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

bool ImportLevel::ImportLevelVectorData(const std::string& fileName)
{

	vectorLevelData_.clear();

	//�t�@�C���X�g���[��
	std::ifstream file(fileName);

	if (!file)
	{
		loadErrorText_ = "can not find file";
		return false;
	}

	//JSON�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;

	//��
	file >> deserialized;

	//�������C�x���g�t�@�C�����`�F�b�N
	if (!deserialized.is_object() || !deserialized.contains("name") || !deserialized["name"].is_string())
	{
		loadErrorText_ = "Not the correct Level file";
		return false;
	}

	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();

	//���������ǂ����`�F�b�N
	if (name.compare("Level") != 0)
	{
		loadErrorText_ = "Not event file";
		return false;
	}

	//"events"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& events : deserialized["objects"])
	{

		bool result = true;

		result = LevelScanning(events);

		if (!result)
		{
			vectorLevelData_.clear();
			return false;
		}
	}


	if (vectorLevelData_.empty())
	{
		vectorLevelData_.push_back(LevelData());
	}

	return true;
}

bool ImportLevel::ImportLevelListData(const std::string& fileName)
{
	listLevelData_.clear();

	//�t�@�C���X�g���[��
	std::ifstream file(fileName);

	if (!file)
	{
		loadErrorText_ = "can not find file";
		return false;
	}

	//JSON�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;

	//��
	file >> deserialized;

	//�������C�x���g�t�@�C�����`�F�b�N
	if (!deserialized.is_object() || !deserialized.contains("name") || !deserialized["name"].is_string())
	{
		loadErrorText_ = "Not the correct Level file";
		return false;
	}

	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();

	//���������ǂ����`�F�b�N
	if (name.compare("Level") != 0)
	{
		loadErrorText_ = "Not event file";
		return false;
	}

	//"events"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& events : deserialized["objects"])
	{

		bool result = true;

		result = LevelScanning(events);

		if (!result)
		{
			listLevelData_.clear();
			return false;
		}
	}


	if (listLevelData_.empty())
	{
		listLevelData_.push_back(LevelData());
	}

	return true;
}

bool ImportLevel::LevelScanning(nlohmann::json& Level)
{

	//type���Ȃ���Ύ~�߂�
	if (!Level.contains("type"))
	{
		loadErrorText_ = "event type is missing";
		return false;
	}
	//�^�C�v���擾
	std::string type = Level["type"].get<std::string>();



	LevelData levelData;

	//�ݒ�̃p�����[�^�ǂݍ���
	nlohmann::json& seting = Level["object"];

	//�ړ�����ꏊ�ǂݍ���
	levelData.pos.x = (float)seting["pos"][0];
	levelData.pos.y = (float)seting["pos"][1];

	//�ړ��J�n�ʒu�擾
	levelData.scale.x = (float)seting["scale"][0];
	levelData.scale.y = (float)seting["scale"][1];

	//�X�s�[�h�̃Z�b�g
	levelData.tag = (ObjectType)seting["tag"];

	vectorLevelData_.push_back(levelData);
	listLevelData_.push_back(levelData);

	return true;

	
}


bool ImportLevel::WindowsOpenLevelFileVector()
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//�\���̂̑傫����{�I�ɂ���
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//�g������(��L)�E�C���h�E�n���h��
	FileObj.hwndOwner = GetMainWindowHandle();
	//�t�B���^�[��ݒ�?
	FileObj.lpstrFilter = "�C�x���g�G�f�B�^�쐬�t�@�C��(eefm)\0 * .eefm*\0"
		"���ׂẴt�@�C�� (*.*)\0*.*\0";
	//���ڂ̃t�B���^�[���g����?�݂����Ȋ���?
	FileObj.nFilterIndex = 0;
	//�ۑ��̎��t�@�C������������?
	FileObj.lpstrFile = filePath;
	//�t�@�C���̃o�b�t�@�̑傫���H
	FileObj.nMaxFile = MAX_PATH;

	auto old = std::filesystem::current_path();
	if (GetOpenFileName(&FileObj))
	{
		
		bool result = true;
		//�ݒ�̂܂Ƃ߂ɑI�������t�@�C����ǂݎ�菑������
		result = ImportLevelVectorData(filePath);

		if (!result)
		{
			
			return false;
		}

	}
	std::filesystem::current_path(old);

	return true;
}

bool ImportLevel::WindowsOpenLevelFileList()
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//�\���̂̑傫����{�I�ɂ���
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//�g������(��L)�E�C���h�E�n���h��
	FileObj.hwndOwner = GetMainWindowHandle();
	//�t�B���^�[��ݒ�?
	FileObj.lpstrFilter = "�C�x���g�G�f�B�^�쐬�t�@�C��(eefm)\0 * .eefm*\0"
		"���ׂẴt�@�C�� (*.*)\0*.*\0";
	//���ڂ̃t�B���^�[���g����?�݂����Ȋ���?
	FileObj.nFilterIndex = 0;
	//�ۑ��̎��t�@�C������������?
	FileObj.lpstrFile = filePath;
	//�t�@�C���̃o�b�t�@�̑傫���H
	FileObj.nMaxFile = MAX_PATH;

	auto old = std::filesystem::current_path();
	if (GetOpenFileName(&FileObj))
	{

		bool result = true;
		//�ݒ�̂܂Ƃ߂ɑI�������t�@�C����ǂݎ�菑������
		result = ImportLevelListData(filePath);

		if (!result)
		{

			return false;
		}

	}
	std::filesystem::current_path(old);

	return true;
}