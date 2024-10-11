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
	//中身消してから使う
	stageObjData_.clear();
	for (auto &level : levelData)
	{
		//タグの内容で決定
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