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
	//�������̓V���O���g������
	static ImportLevel* GetInstance();

	

	bool WindowsOpenLevelFileVector();
	bool WindowsOpenLevelFileList();
	
private:

	//�V���O���g���p
	ImportLevel() = default;
	~ImportLevel();

	ImportLevel(const ImportLevel&) = delete;
	ImportLevel& operator=(const ImportLevel&) = delete;


	//����Ă����f�[�^������̔z��ɓ����
	//�f�[�^��vector�z��ɓ����
	bool ImportLevelVectorData(const std::string& fileName);
	//�f�[�^��list�z��ɓ����
	bool ImportLevelListData(const std::string& fileName);
	//���x���̒��g�ǂݍ��ނ悤
	bool LevelScanning(nlohmann::json& Level);


public:

	bool isLoad_ = true;

private:

	//�ꎞ�ۑ��p�ł���{�I�ɒ��g�Ȃ�
	std::vector<LevelData> vectorLevelData_;
	std::list<LevelData> listLevelData_;

	std::string loadErrorText_;

};

