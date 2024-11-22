#include "LevelPreview.h"
#include "DxLib.h"
#include "TextureManager.h"

LevelPreView::LevelPreView()
{
}

LevelPreView::~LevelPreView()
{
}

void LevelPreView::Initialize()
{
	lockhandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\DoorKey.png");
}

void LevelPreView::Update(std::string selectFileName)
{

	if (nowSelectfileName_ != selectFileName)
	{
		LoadStageObjectFile(selectFileName);
		nowSelectfileName_ = selectFileName;
	}


}

void LevelPreView::Draw()
{
	DrawBoxAA(pos_.x, pos_.y, pos_.x + (float)WIN_WIDTH * size_.x, pos_.y + (float)WIN_HEIGHT * size_.y, 0x000000, true);

	for (auto& data : previewData_)
	{
		DrawRotaGraph3F((pos_.x + (data.pos_.x - data.size_.x / 2) * size_.x), (pos_.y + (data.pos_.y - data.size_.y / 2) * size_.y), 0, 0, size_.x, size_.y, 0, data.handle_, true);
		if (lockDoor_ && data.tag_== ObjectType::GOAL)
		{
			DrawRotaGraph3F((pos_.x + (data.pos_.x - data.size_.x / 2) * size_.x), (pos_.y + (data.pos_.y - data.size_.y / 2) * size_.y), 0, 0, size_.x, size_.y, 0, lockhandle_, true);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(colA[3] * 255));
	DrawBoxAA(pos_.x, pos_.y, pos_.x + (float)WIN_WIDTH * size_.x, pos_.y + (float)waterHorizontal_ * size_.y, GetColor((int)(colA[0] * 255), (int)(colA[1] * 255), (int)(colA[2] * 255)), true);
	DrawBoxAA(pos_.x, pos_.y + (float)waterHorizontal_ * size_.y, pos_.x + (float)WIN_WIDTH * size_.x, pos_.y + (float)WIN_HEIGHT * size_.y, GetColor((int)(colB[0] * 255), (int)(colB[1] * 255), (int)(colB[2] * 255)), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawLineAA(pos_.x, pos_.y + (float)waterHorizontal_ * size_.y, pos_.x + (float)WIN_WIDTH * size_.x, pos_.y + (float)waterHorizontal_ * size_.y, GetColor(100, 255, 255));
}

void LevelPreView::LoadStageObjectFile(const std::string& fileName)
{
	InputLevelData loadData;

	loadData = ImportLevel::GetInstance()->ImportLevelListData(fileName);
	if (loadData.isLoad)
	{
		LoadListStageData(loadData.levelData);
		waterHorizontal_=loadData.horizontal;
	}
	else
	{
		loadData = ImportLevel::GetInstance()->ImportLevelListData("Error");
		if (loadData.isLoad)
		{
			LoadListStageData(loadData.levelData);
			waterHorizontal_ = loadData.horizontal;
		}
	}

}

void LevelPreView::LoadListStageData(std::list<LevelData> levelData)
{
	//’†gÁ‚µ‚Ä‚©‚çŽg‚¤
	previewData_.clear();

	for (auto& data : levelData)
	{
		if (data.tag == ObjectType::KEY)
		{
			lockDoor_ = true;
		}
	}
	for (auto& level : levelData)
	{
		AddObject(level.pos, level.scale, level.tag);
	}

}

void LevelPreView::AddObject(Vector2 pos, Vector2 size, ObjectType tag)
{
	PreViewData addObject;

	addObject.pos_ = pos;
	addObject.size_ = size;
	addObject.tag_ = tag;

	switch (tag)
	{
	case ObjectType::PLAYER:
	
		addObject.handle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Player.png");
		break;
	case ObjectType::SPONGE_BLOCK:

		addObject.handle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\OpenDoor.png");
		break;

	case ObjectType::FLOAT_BLOCK:
		
		addObject.handle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\FloatBlook.png");
		break;

	case ObjectType::NOT_FLOAT_BLOCK:
		
		addObject.handle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\OpenDoor.png");
		break;

	case ObjectType::BREAK_BLOCK:
		
		addObject.handle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\OpenDoor.png");
		break;
	case ObjectType::GOAL:
		
		addObject.handle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\CloseDoor.png");
		break;
	case ObjectType::KEY:
		
		addObject.handle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Key.png");
		break;
	case ObjectType::DRAIN:

		addObject.handle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\OpenDoor.png");
		break;
	default:
		return;
		break;
	}

	previewData_.push_back(addObject);
}