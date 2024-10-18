#include "StageManager.h"

StageManager* StageManager::GetInstance()
{
	static StageManager instance;
	return &instance;
}

StageManager::~StageManager()
{
}

void StageManager::LoadListStageData(std::list<LevelData> levelData)
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

void StageManager::EditorUpdate()
{

}

void StageManager::addObject(Vector2 pos, Vector2 size, ObjectType tag)
{
	//�^�O�̓��e�Ō���
	switch (tag)
	{
	case ObjectType::PLAYER:
		break;

	case ObjectType::FLOAT_BLOCK:
		break;

	default:
		break;
	}
}