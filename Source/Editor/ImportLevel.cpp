#include "ImportLevel.h"
#include <sstream>
#include <fstream>
#include <cstdint>
#include<string>

ImportLevel::ImportLevel()
{
}

ImportLevel::~ImportLevel()
{
}

std::vector<LevelData> ImportLevel::ImportLevelVectorData(const std::string& fileName)
{

	std::vector<LevelData> levelData;
	//�t�@�C���X�g���[��
	std::ifstream file(fileName);

	if (!file)
	{
		assert(0);
	}

	//JSON�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;

	//��
	file >> deserialized;

	//�������C�x���g�t�@�C�����`�F�b�N
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();

	//���g�����������ǂ����`�F�b�N
	assert(name.compare("Level") == 0);

	//"events"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& objects : deserialized["objects"])
	{

		levelData.push_back(LevelScanning(objects));
	}
	
	if (levelData.empty())
	{
		levelData.push_back(LevelData());
	}

	return levelData;
}

std::list<LevelData> ImportLevel::ImportLevelListData(const std::string& fileName)
{
	std::list<LevelData> levelData;
	//�t�@�C���X�g���[��
	std::ifstream file(fileName);

	if (!file)
	{
		assert(0);
	}

	//JSON�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;

	//��
	file >> deserialized;

	//�������C�x���g�t�@�C�����`�F�b�N
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();

	//���g�����������ǂ����`�F�b�N
	assert(name.compare("Level") == 0);

	//"events"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& objects : deserialized["objects"])
	{

		levelData.push_back(LevelScanning(objects));
	}

	if (levelData.empty())
	{
		levelData.push_back(LevelData());
	}

	return levelData;
}

LevelData ImportLevel::LevelScanning(nlohmann::json& Level)
{


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

	return levelData;
	
}
