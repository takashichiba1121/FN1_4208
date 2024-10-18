#include "StageManager.h"
#include "Player.h"
#include "Block.h"
#include "levitationBlock.h"

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
	//中身消してから使う
	stageObjData_.clear();
	for (auto &level : levelData)
	{
		AddObject(level.pos, level.scale, level.tag);
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


void StageManager::AddObject(Vector2 pos, Vector2 size, ObjectType tag)
{
	std::unique_ptr<Object> addObject;
	//タグの内容で決定
	switch (tag)
	{
	case ObjectType::PLAYER:
		addObject = std::make_unique<Player>();

		addObject->SetPos(pos);
		addObject->SetSize(size);
		addObject->

		stageObjData_.push_back(std::move(addObject));

		break;

	case ObjectType::FLOAT_BLOCK:
		addObject = std::make_unique<LevitationBlock>();

		addObject->SetPos(pos);
		addObject->SetSize(size);

		stageObjData_.push_back(std::move(addObject));
		break;

	case ObjectType::NOT_FLOAT_BLOCK:
		addObject = std::make_unique<Block>();

		addObject->SetPos(pos);
		addObject->SetSize(size);

		stageObjData_.push_back(std::move(addObject));
		break;

	default:
		break;
	}
}