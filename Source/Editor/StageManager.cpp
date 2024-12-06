#include "StageManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Block.h"
#include "Goal.h"
#include "levitationBlock.h"
#include "BreakBlock.h"
#include "Water.h"
#include "Window.h"
#include "Key.h"
#include "SpongeBlock.h"
#include "Drain.h"
#include "TutorialObject.h"

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
	CollisionManager::GetInstance()->AllDelete();
	for (auto &level : levelData)
	{
		AddObject(level.pos, level.scale, level.tag,level.seting);
	}

}

void StageManager::LoadStageObjectFile(const std::string& fileName)
{
	InputLevelData loadData;

	loadData = ImportLevel::GetInstance()->ImportLevelListData(fileName);
	if (loadData.isLoad)
	{
		LoadListStageData(loadData.levelData);
		Water::GetInstance()->SetHorizontal(loadData.horizontal);
	}
	else
	{
		loadData = ImportLevel::GetInstance()->ImportLevelListData("Error");
		if (loadData.isLoad)
		{
			LoadListStageData(loadData.levelData);
			Water::GetInstance()->SetHorizontal(loadData.horizontal);
		}
	}
	
}

void StageManager::Initialize()
{
	//ステージとして使いたいファイル名をここに追加
	stageFileName_ = {
		"Error",
		"test3",
		"test4",
		"",
	};
}

void StageManager::Update()
{

#ifdef _DEBUG

	if (isUseEditer_)return;

#endif

	for (auto &level : stageObjData_)
	{
		level->Update();
	}
}

void StageManager::Inversion(const float easing) {
	for (auto& level : stageObjData_)
	{
		level->Inversion(easing);
	}
}

void StageManager::SetTentPos() {
	for (auto& level : stageObjData_)
	{
		level->SetTent();
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
	std::unique_ptr<Object> addObject = SelectObject(tag);

	if (tag == ObjectType::KEY)
	{
		KeyNum_++;
	}

	addObject->Initialize();

	addObject->SetPos(pos);
	addObject->SetSize(size);
	addObject->SetObjectType(tag);

	stageObjData_.push_back(std::move(addObject));
}

void StageManager::AddObject(Vector2 pos, Vector2 size, ObjectType tag, nlohmann::json seting)
{
	std::unique_ptr<Object> addObject = SelectObject(tag);
	
	if (tag == ObjectType::KEY)
	{
		KeyNum_++;
	}

	addObject->Initialize();

	addObject->GetJson(seting);

	addObject->SetPos(pos);
	addObject->SetSize(size);
	addObject->SetObjectType(tag);

	stageObjData_.push_back(std::move(addObject));
}

void StageManager::ChengeTag(const std::list<std::unique_ptr<Object>>::iterator& chengeData, ObjectType tag)
{
	std::unique_ptr<Object> addObject= SelectObject(tag);
	
	if (chengeData->get()->GetObjectType() != ObjectType::KEY && tag == ObjectType::KEY)
	{
		KeyNum_++;
	}
	else if(chengeData->get()->GetObjectType() == ObjectType::KEY && tag != ObjectType::KEY)
	{
		KeyNum_--;
	}

	addObject->Initialize();

	addObject->SetPos(chengeData->get()->GetPos());
	addObject->SetSize(chengeData->get()->GetSize());
	addObject->SetObjectType(tag);

	chengeData->swap(addObject);
}

void StageManager::SelectLevelNum(int32_t selectNum)
{
	LoadStageObjectFile(stageFileName_[selectNum]);
	nowLevelNum_ = selectNum;
}

void StageManager::NextLevelLoad()
{
	if (nowLevelNum_ + 1 > stageFileName_.size()-1)
	{
		SceneManager::GetInstance()->ChangeScene("STAGESELECT");
		return;
	}

	CollisionManager::GetInstance()->AllDelete();
	LoadStageObjectFile(stageFileName_[nowLevelNum_+1]);	
	nowLevelNum_ = nowLevelNum_ + 1;
}

std::unique_ptr<Object> StageManager::SelectObject(ObjectType tag)
{
	std::unique_ptr<Object> addObject;
	//タグの内容で決定
	switch (tag)
	{
	case ObjectType::PLAYER:
		addObject = std::make_unique<Player>();

		break;
	case ObjectType::SPONGE_BLOCK:
		addObject = std::make_unique<SpongeBlock>();

		break;

	case ObjectType::FLOAT_BLOCK:
		addObject = std::make_unique<LevitationBlock>();

		break;

	case ObjectType::NOT_FLOAT_BLOCK:
		addObject = std::make_unique<Block>();

		break;

	case ObjectType::BREAK_BLOCK:
		addObject = std::make_unique<BreakBlock>();

		break;
	case ObjectType::GOAL:
		addObject = std::make_unique<Goal>();

		break;
	case ObjectType::KEY:
		addObject = std::make_unique<Key>();

		break;
	case ObjectType::DRAIN:
		addObject = std::make_unique<Drain>();

		break;
	case ObjectType::TUTORIAL:
		addObject = std::make_unique<TutorialObject>();

		break;
	default:
		addObject = std::make_unique<Block>();
		break;
	}

	return std::move(addObject);
}