#include "StageManager.h"

StageManager* StageManager::GetInstance()
{
	static StageManager instance;
	return &instance;
}

StageManager::~StageManager()
{
}

std::list<std::unique_ptr<Object>> StageManager::LoadListStageData(std::list<LevelData> levelData)
{
	//���g�����Ă���g��
	stageObjData_.clear();
	for (auto &level : levelData)
	{
		//�^�O�̓��e�Ō���
		switch (level.tag)
		{
		case ObjectType::PLAYER:
			break;

		case ObjectType::FLOAT_BLOCK:
			break;

		default:
			break;
		}
	}

	return stageObjData_;
}

void StageManager::Update()
{
	for (auto &level : stageObjData_)
	{
		level->Update();
	}
}

void StageManager::Draw()
{
	for (auto &level : stageObjData_)
	{
		level->Draw();
	}
}