#include "ImportLevel.h"
#include <sstream>
#include <fstream>
#include <cstdint>
#include<string>

ImportLevel* ImportLevel::GetInstance()
{
	static ImportLevel instance;
	return &instance;
}
ImportLevel::~ImportLevel()
{
}

InputLevelData ImportLevel::ImportLevelVectorData(const std::string& fileName)
{

	vectorLevelData_.clear();

	InputLevelData output;

	//�t�@�C���X�g���[��
	std::ifstream file(fileName);

	if (!file)
	{
		loadErrorText_ = "can not find file";
		output.isLoad = false;
		return output;
	}

	//JSON�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;

	//��
	file >> deserialized;

	//�������C�x���g�t�@�C�����`�F�b�N
	if (!deserialized.is_object() || !deserialized.contains("name") || !deserialized["name"].is_string())
	{
		loadErrorText_ = "Not the correct Level file";
		output.isLoad = false;
		return output;
	}

	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();

	//���������ǂ����`�F�b�N
	if (name.compare("Level") != 0)
	{
		loadErrorText_ = "Not LevelEditor file";
		output.isLoad = false;
		return output;
	}

	//"events"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& events : deserialized["objects"])
	{

		bool result = true;

		result = LevelScanning(events);

		if (!result)
		{
			vectorLevelData_.clear();
			output.isLoad = false;
			return output;
		}
	}


	if (vectorLevelData_.empty())
	{
		vectorLevelData_.push_back(LevelData());
	}

	loadErrorText_ = "";
	output.levelData = listLevelData_;
	output.isLoad = true;

	listLevelData_.clear();
	vectorLevelData_.clear();
	return output;
}

InputLevelData ImportLevel::ImportLevelListData(const std::string& fileName)
{
	listLevelData_.clear();

	InputLevelData output;

	//�t�@�C���X�g���[��
	std::ifstream file(fileName);

	if (!file)
	{
		loadErrorText_ = "can not find file";
		output.isLoad = false;
		return output;
	}

	//JSON�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;

	//��
	file >> deserialized;

	//�������C�x���g�t�@�C�����`�F�b�N
	if (!deserialized.is_object() || !deserialized.contains("name") || !deserialized["name"].is_string())
	{
		loadErrorText_ = "Not the correct Level file";
		output.isLoad = false;
		return output;
	}

	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();

	//���������ǂ����`�F�b�N
	if (name.compare("Level") != 0)
	{
		loadErrorText_ = "Not LevelEditor file";
		output.isLoad = false;
		return output;
	}

	//"events"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& events : deserialized["objects"])
	{

		bool result = true;

		result = LevelScanning(events);

		if (!result)
		{
			listLevelData_.clear();
			output.isLoad = false;
			return output;
		}
	}


	if (listLevelData_.empty())
	{
		listLevelData_.push_back(LevelData());
	}

	loadErrorText_ = "";
	output.levelData = listLevelData_;
	output.isLoad = true;

	listLevelData_.clear();
	vectorLevelData_.clear();
	return output;
}

bool ImportLevel::LevelScanning(nlohmann::json& Level)
{

	////type���Ȃ���Ύ~�߂�
	//if (!Level.contains("type"))
	//{
	//	loadErrorText_ = "event type is missing";
	//	return false;
	//}
	////�^�C�v���擾
	//std::string type = Level["type"].get<std::string>();



	LevelData levelData;

	//�ݒ�̃p�����[�^�ǂݍ���
	nlohmann::json& seting = Level["object"];

	//�ʒu�ǂݍ���
	levelData.pos.x = (float)seting["pos"][0];
	levelData.pos.y = (float)seting["pos"][1];

	//�傫���擾
	levelData.scale.x = (float)seting["scale"][0];
	levelData.scale.y = (float)seting["scale"][1];

	//���
	levelData.tag = ObjectName::ObjectString((int32_t)seting["tag"]);

	vectorLevelData_.push_back(levelData);
	listLevelData_.push_back(levelData);

	return true;

	
}


InputLevelData ImportLevel::WindowsOpenLevelFileVector()
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//�\���̂̑傫����{�I�ɂ���
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//�g������(��L)�E�C���h�E�n���h��
	FileObj.hwndOwner = GetMainWindowHandle();
	//�t�B���^�[��ݒ�?
	FileObj.lpstrFilter = "�X�e�[�W�G�f�B�^�쐬�t�@�C��\0 * .json*\0"
		"���ׂẴt�@�C�� (*.*)\0*.*\0";
	//���ڂ̃t�B���^�[���g����?�݂����Ȋ���?
	FileObj.nFilterIndex = 0;
	//�ۑ��̎��t�@�C������������?
	FileObj.lpstrFile = filePath;
	//�t�@�C���̃o�b�t�@�̑傫���H
	FileObj.nMaxFile = MAX_PATH;

	auto old = std::filesystem::current_path();
	InputLevelData result;
	if (GetOpenFileName(&FileObj))
	{
		//�ݒ�̂܂Ƃ߂ɑI�������t�@�C����ǂݎ�菑������
		result = ImportLevelVectorData(filePath);

		if (!result.isLoad)
		{
			return result;
		}

	}
	std::filesystem::current_path(old);
	result.levelData = listLevelData_;
	result.isLoad = true;
	return result;
}

InputLevelData ImportLevel::WindowsOpenLevelFileList()
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//�\���̂̑傫����{�I�ɂ���
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//�g������(��L)�E�C���h�E�n���h��
	FileObj.hwndOwner = GetMainWindowHandle();
	//�t�B���^�[��ݒ�?
	FileObj.lpstrFilter = "�X�e�[�W�G�f�B�^�쐬�t�@�C��\0 * .json*\0"
		"���ׂẴt�@�C�� (*.*)\0*.*\0";
	//���ڂ̃t�B���^�[���g����?�݂����Ȋ���?
	FileObj.nFilterIndex = 0;
	//�ۑ��̎��t�@�C������������?
	FileObj.lpstrFile = filePath;
	//�t�@�C���̃o�b�t�@�̑傫���H
	FileObj.nMaxFile = MAX_PATH;

	auto old = std::filesystem::current_path();
	InputLevelData result;
	if (GetOpenFileName(&FileObj))
	{
		//�ݒ�̂܂Ƃ߂ɑI�������t�@�C����ǂݎ�菑������
		result = ImportLevelListData(filePath);

		if (!result.isLoad)
		{
			return result;
		}

	}
	std::filesystem::current_path(old);

	result.levelData = listLevelData_;
	result.isLoad = true;
	return result;
}