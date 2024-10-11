#include "EditStage.h"
#include "DxLib.h"
#include <fstream>

EditStage::EditStage()
{
}

EditStage::~EditStage()
{
}

void EditStage::Initialize()
{
	
}

void EditStage::Update()
{
	
}

void EditStage::Draw()
{

}

void EditStage::WindowsSaveFile(std::vector<std::unique_ptr<Object>> saveData)
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//�\���̂̑傫����{�I�ɂ���
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//�g������(��L)�E�C���h�E�n���h��
	FileObj.hwndOwner = GetMainWindowHandle();
	//�t�B���^�[��ݒ�?
	FileObj.lpstrFilter = "�X�e�[�W�G�f�B�^�쐬�t�@�C��\0 * .json*\0\0";
	//�g���q����
	FileObj.lpstrDefExt = "json";
	//���ڂ̃t�B���^�[���g����?�݂����Ȋ���?
	FileObj.nFilterIndex = 0;
	//�ۑ��̎��t�@�C������������?
	FileObj.lpstrFile = filePath;
	//�t�@�C���̃o�b�t�@�̑傫���H
	FileObj.nMaxFile = MAX_PATH;
	//�t�@�C����ۑ�����Ƃ��ɂǂ��������������邩
	FileObj.Flags = OFN_OVERWRITEPROMPT;

	auto old = std::filesystem::current_path();
	if (GetSaveFileName(&FileObj))
	{
		SaveLevelFullPathData(filePath,saveData);
	}
	std::filesystem::current_path(old);
}

void EditStage::WindowsSaveFile(std::list<std::unique_ptr<Object>> saveData)
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//�\���̂̑傫����{�I�ɂ���
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//�g������(��L)�E�C���h�E�n���h��
	FileObj.hwndOwner = GetMainWindowHandle();
	//�t�B���^�[��ݒ�?
	FileObj.lpstrFilter = "�X�e�[�W�G�f�B�^�쐬�t�@�C��\0 * .json*\0\0";
	//�g���q����
	FileObj.lpstrDefExt = "json";
	//���ڂ̃t�B���^�[���g����?�݂����Ȋ���?
	FileObj.nFilterIndex = 0;
	//�ۑ��̎��t�@�C������������?
	FileObj.lpstrFile = filePath;
	//�t�@�C���̃o�b�t�@�̑傫���H
	FileObj.nMaxFile = MAX_PATH;
	//�t�@�C����ۑ�����Ƃ��ɂǂ��������������邩
	FileObj.Flags = OFN_OVERWRITEPROMPT;

	auto old = std::filesystem::current_path();
	if (GetSaveFileName(&FileObj))
	{
		SaveLevelFullPathData(filePath, saveData);
	}
	std::filesystem::current_path(old);
}

void EditStage::SaveLevelFullPathData(const std::string& fileName, std::vector<std::unique_ptr<Object>> saveData)
{
	std::string name = fileName;

	//�������O���󔒂Ȃ�K���Ȗ��O��
	if (fileName == "")
	{
		name = std::string("jsonEventdata");
	}

	nlohmann::json jsonfile;

	//�Ǘ���
	jsonfile["name"] = "Level";

	for (auto &levelData : saveData)
	{
		nlohmann::json data;
		
		//object�Ƃ����ł܂�̒��ɏ�������
		data["object"]["pos"] = { levelData->GetPos().x,levelData->GetPos().y};
		data["object"]["scale"] = { levelData->GetSize().x,levelData->GetSize().y };
		data["object"]["tag"] = { };
		
		//�S�̂̌ł܂�ɓ����
		jsonfile["objects"] += { data };
	}

	//�C���f���g������炵��
	std::ofstream ofs(name);
	if (ofs) {
		ofs << jsonfile.dump(4);
	}
}

void EditStage::SaveLevelFullPathData(const std::string& fileName, std::list<std::unique_ptr<Object>> saveData)
{
	std::string name = fileName;

	//�������O���󔒂Ȃ�K���Ȗ��O��
	if (fileName == "")
	{
		name = std::string("jsonEventdata");
	}

	nlohmann::json jsonfile;

	//�Ǘ���
	jsonfile["name"] = "Level";

	for (auto& levelData : saveData)
	{
		nlohmann::json data;

		//object�Ƃ����ł܂�̒��ɏ�������
		data["object"]["pos"] = { levelData->GetPos().x,levelData->GetPos().y };
		data["object"]["scale"] = { levelData->GetSize().x,levelData->GetSize().y };
		data["object"]["tag"] = { };

		//�S�̂̌ł܂�ɓ����
		jsonfile["objects"] += { data };
	}

	//�C���f���g������炵��
	std::ofstream ofs(name);
	if (ofs) {
		ofs << jsonfile.dump(4);
	}
}