#pragma once
//���x���f�[�^��ǂݍ���ŕԂ��N���X

#include "DxLib.h"
#include "Vector2.h"
#include "vector"
#include <memory>
#include "Object.h"

//json�̓ǂݍ��݂Ƃ��Ɏg��
#pragma warning( push )
#pragma warning( disable : 26819 )
#include "json.hpp"
#pragma warning( pop )

struct LevelData
{
	//��{���
	Vector2 pos;
	Vector2 scale;

	//���g(���enum�ɕς��邩��)
	ObjectType tag = ObjectType::PLAYER;
};

class ImportLevel
{
public:
	ImportLevel();
	~ImportLevel();

	//����Ă����f�[�^������̔z��ɓ����
	//�f�[�^��vector�z��ɓ����
	static std::vector<LevelData> ImportLevelVectorData(const std::string& fileName);
	//�f�[�^��list�z��ɓ����
	static std::list<LevelData> ImportLevelListData(const std::string& fileName);

	//���x���̒��g�ǂݍ��ނ悤
	static LevelData LevelScanning(nlohmann::json& Level);


private:

};

