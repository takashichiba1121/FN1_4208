#pragma once
#include "DxLib.h"
#include "Object.h"
#include "ImportLevel.h"
#include <vector>
#include <memory>
#include <list>
#include <sstream>

class StageManager
{
public:
	//�������̓V���O���g������
	static StageManager* GetInstance();

	//std::vector<Object> LoadStageData(const std::string& fileName);
	std::list<std::unique_ptr<Object>> LoadListStageData(std::list<LevelData> levelData);

	//���ǂݍ���ł�f�[�^�̃|�C���^��Ԃ�
	std::list<std::unique_ptr<Object>>* GetObjectList() { return &stageObjData_; };

	void Update();

	void Draw();

private:

	//�V���O���g���p
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

	//�G�f�B�^�p�̍X�V
	void EditorUpdate();

	void addObject(Vector2 pos, Vector2 size, ObjectType tag);

private:

	std::list<std::unique_ptr<Object>> stageObjData_;

};

