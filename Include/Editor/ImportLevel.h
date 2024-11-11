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

//�ǂݍ��񂾎��A���Ă���f�[�^
struct InputLevelData
{
	std::list<LevelData> levelData;

	float horizontal = 0.0f;

	bool isLoad = false;

};


struct ObjectName
{
	static ObjectType ObjectString(int32_t objectNum)
	{
		if (objectNum == static_cast<int32_t>(ObjectType::PLAYER))
		{
			return ObjectType::PLAYER;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::FLOAT_BLOCK))
		{
			return ObjectType::FLOAT_BLOCK;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::NOT_FLOAT_BLOCK))
		{
			return ObjectType::NOT_FLOAT_BLOCK;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::BREAK_BLOCK))
		{
			return ObjectType::BREAK_BLOCK;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::GOAL))
		{
			return ObjectType::GOAL;
		}

		return ObjectType::NONE;
	}
};

class ImportLevel
{
public:
	//�������̓V���O���g������
	static ImportLevel* GetInstance();

	

	InputLevelData WindowsOpenLevelFile();

	//�f�[�^��list�z��ɓ����
	InputLevelData ImportLevelListData(const std::string& fileName);

	std::string GetLoadErrorText() { return loadErrorText_; };
	
private:

	//�V���O���g���p
	ImportLevel() = default;
	~ImportLevel();

	ImportLevel(const ImportLevel&) = delete;
	ImportLevel& operator=(const ImportLevel&) = delete;


	//����Ă����f�[�^������̔z��ɓ����
	//�f�[�^��vector�z��ɓ����
	//InputLevelData ImportLevelVectorData(const std::string& fileName);
	
	//���x���̒��g�ǂݍ��ނ悤
	bool LevelScanning(nlohmann::json& Level);

private:

	//�ꎞ�ۑ��p�ł���{�I�ɒ��g�Ȃ�
	std::vector<LevelData> vectorLevelData_;
	std::list<LevelData> listLevelData_;

	std::string loadErrorText_;

};

