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

	nlohmann::json seting;

	//���g(���enum�ɕς��邩��)
	ObjectType tag = ObjectType::PLAYER;
};

//�ǂݍ��񂾎��A���Ă���f�[�^
struct InputLevelData
{
	std::list<LevelData> levelData;

	//�X�e�[�W�̖��O�Ƃ������Ƃ�
	std::string LevelName_ = "";

	float horizontal = 0.0f;

	bool isLoad = false;

};


struct ObjectName
{
	//������Ή�����enumclass�ŕԂ��֐�
	template <typename Enum>
	static Enum ObjectString(int value) {
	for (int32_t i = static_cast<int32_t>(ObjectType::PLAYER); i <= static_cast<int32_t>(ObjectType::NONE); i++) 
	{
			if (i == value) 
			{
				return static_cast<Enum>(i);
			}
		}
		return static_cast<Enum>(ObjectType::NONE);
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
	InputLevelData ImportLevelListDataFullPath(const std::string& fileName);

	std::string GetLoadErrorText() { return loadErrorText_; };
	
private:

	//�V���O���g���p
	ImportLevel() = default;
	~ImportLevel();

	ImportLevel(const ImportLevel&) = delete;
	ImportLevel& operator=(const ImportLevel&) = delete;
	
	//���x���̒��g�ǂݍ��ނ悤
	bool LevelScanning(nlohmann::json& Level);

private:

	//�ꎞ�ۑ��p�ł���{�I�ɒ��g�Ȃ�
	std::vector<LevelData> vectorLevelData_;
	std::list<LevelData> listLevelData_;

	std::string loadErrorText_;

	//�ǂݍ��ލۂ̃t�@�C���p�X(�t�@�C���������Ŏw�肷�邽��)
	static const inline std::string SDefaultEventPath_ = "Resources/Level/";

	//�t�@�C���g���q
	static const inline std::string SDefaultEventExtension_ = ".json";

};

