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
#include "Water.h"
#include "TextureManager.h"
#include"Input.h"

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
	for (auto& level : levelData)
	{
		AddObject(level.pos, level.scale, level.tag, level.seting);
	}

	//オブジェクトの描画順を変えるためにオブジェクトタイプの順番にする
	for (int32_t i = static_cast<int32_t>(ObjectType::NONE); i >= static_cast<int32_t>(ObjectType::PLAYER); i--)
	{
		for (auto object : stageObjUnSortData_)
		{
			if (object->GetObjectType() == ObjectName::ObjectString<ObjectType>(i))
			{
				stageObjData_.push_back(std::move(object));
			}
		}
	}
	stageObjUnSortData_.clear();
}

void StageManager::LoadStageObjectFile(const std::string& fileName)
{
	InputLevelData loadData;
	//本当に一応消してるだけ
	CollisionManager::GetInstance()->AllDelete();
	stageObjData_.clear();
	KeyNum_ = 0;

	loadData = ImportLevel::GetInstance()->ImportLevelListData(fileName);
	if (loadData.isLoad)
	{
		LoadListStageData(loadData.levelData);
		Water::GetInstance()->SetHorizontal(loadData.horizontal);
		nowLevelStageName_ = loadData.LevelName_;
	}
	else
	{
		loadData = ImportLevel::GetInstance()->ImportLevelListData("Error");
		if (loadData.isLoad)
		{
			LoadListStageData(loadData.levelData);
			Water::GetInstance()->SetHorizontal(loadData.horizontal);
			nowLevelStageName_ = loadData.LevelName_;
		}
	}

}

void StageManager::Initialize()
{
	//ステージとして使いたいファイル名をここに追加
	stageFileName_ = {
		"test3",
		"test4",
		"oogami_10",
		"fukuyama_1_remake",
		"oogami_3",
		"oogami_4",
		"fukuyama_3",
		"oogami_5",
		"oogami_1",
		"fukuyama_4_remake",
		"chiba3",
		"tominaga_1",
		"fukuyama_6",
		"fukuyama_7",
		"oogami_7",
		"chiba1",
		"fukuyama_2",
		"fukuyama_8",
		"yamashita_1",
		"chiba2",
		"fukuyama_5",
		"oogami_2",
		"oogami_11",
		"oogami_12",
		"tominaga_2",
		"oogami_6",
		"tominaga_3",
		"oogami_8",
		"tominaga_4",
		"oogami_9",
		"tominaga_5",
		"tominaga_6",
		"tominaga_7",
	};

	//パーティクル初期化
	confettiEmitter.Initialize(5);

	clearTextTextruehandle1_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\clear.png");
	clearTextTextruehandle2_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\next.png");
	clearTextTextruehandle3_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\back.png");
	SelectClearTextTextruehandle2_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\SelectNext.png");
	SelectClearTextTextruehandle3_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\SelectBack.png");
	SelectClearTextTextruehandle4_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\SelectButton.png");
	SelectClearTextTextruehandle5_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\SelectPadButton.png");
}

void StageManager::Update()
{

#ifdef _DEBUG

	if (isUseEditer_)return;

#endif

	for (auto& level : stageObjData_)
	{
		level->Update();
		if (isNextLoad_)
		{
			isNextLoad_ = false;
			break;
		}
	}

	if (isClear_)
	{
		confettiEmitter.Update();
		if (easingFrame_ < maxEasingFrame_)
		{

			clearTextSize_ = 1 - cosf(((easingFrame_ / maxEasingFrame_) * 3.141592f) / 2);
			easingFrame_++;
		}

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
	for (auto& level : stageObjData_)
	{
		level->Draw();
	}

	if (isClear_) {
		//クリア
		confettiEmitter.Draw();
		//ゴールの文字

		if (WIN_HEIGHT - (GetGraphSize(clearTextTextruehandle1_).y - 64) * clearTextSize_ <= Water::GetInstance()->GetHorizontal())
		{
			DrawRotaGraph3F(WIN_WIDTH / 2, WIN_HEIGHT - (GetGraphSize(clearTextTextruehandle1_).y - 64) * clearTextSize_, GetGraphSize(clearTextTextruehandle1_).x / 2, GetGraphSize(clearTextTextruehandle1_).y / 2, clearTextSize_ * 1.5f, clearTextSize_ * 1.5f, 0, clearTextTextruehandle1_, TRUE);
		}
		else if ((GetGraphSize(clearTextTextruehandle1_).y - 74) * clearTextSize_ <= Water::GetInstance()->GetHorizontal())
		{
			DrawRotaGraph3F(WIN_WIDTH / 2, 0 + (GetGraphSize(clearTextTextruehandle1_).y - 74) * clearTextSize_, GetGraphSize(clearTextTextruehandle1_).x / 2, GetGraphSize(clearTextTextruehandle1_).y / 2, clearTextSize_ * 1.5f, clearTextSize_ * 1.5f, 0, clearTextTextruehandle1_, TRUE);
		}
		else
		{
			DrawRotaGraph3F(WIN_WIDTH / 2, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle1_).x / 2, GetGraphSize(clearTextTextruehandle1_).y / 2, clearTextSize_ * 1.5f, clearTextSize_ * 1.5f, 0, clearTextTextruehandle1_, TRUE);
		}
		if (Input::GetIsUsePad())
		{
			//下
			if (WIN_HEIGHT - 256 / 4 <= Water::GetInstance()->GetHorizontal())
			{
				if (nextStageSelect_ == -1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4 - 16, (WIN_HEIGHT - GetGraphSize(clearTextTextruehandle3_).y / 4) - 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle5_, TRUE);
				}
				else if (nextStageSelect_ == 1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F((WIN_WIDTH - WIN_WIDTH / 4) - 16, (WIN_HEIGHT - GetGraphSize(clearTextTextruehandle2_).y / 4) - 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle5_, TRUE);
				}
				else
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
				}
			}
			//上
			else if (256 / 4 >= Water::GetInstance()->GetHorizontal())
			{
				if (nextStageSelect_ == -1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4 - 16, (0 + GetGraphSize(clearTextTextruehandle3_).y / 4) + 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle5_, TRUE);
				}
				else if (nextStageSelect_ == 1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F((WIN_WIDTH - WIN_WIDTH / 4) - 16, (0 + GetGraphSize(clearTextTextruehandle2_).y / 4) + 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle5_, TRUE);
				}
				else
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
				}
			}
			else//真ん中
			{
				if (nextStageSelect_ == -1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4 - 16, Water::GetInstance()->GetHorizontal() - 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle5_, TRUE);
				}
				else if (nextStageSelect_ == 1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F((WIN_WIDTH - WIN_WIDTH / 4) - 16, Water::GetInstance()->GetHorizontal() - 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle5_, TRUE);
				}
				else
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
				}
			}
		}
		else
		{
			//下
			if (WIN_HEIGHT - 256 / 4 <= Water::GetInstance()->GetHorizontal())
			{
				if (nextStageSelect_ == -1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4 - 64, (WIN_HEIGHT - GetGraphSize(clearTextTextruehandle3_).y / 4) - 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle4_, TRUE);
				}
				else if (nextStageSelect_ == 1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F((WIN_WIDTH - WIN_WIDTH / 4) - 64, (WIN_HEIGHT - GetGraphSize(clearTextTextruehandle2_).y / 4) - 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle4_, TRUE);
				}
				else
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, WIN_HEIGHT - GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
				}
			}
			//上
			else if (256 / 4 >= Water::GetInstance()->GetHorizontal())
			{
				if (nextStageSelect_ == -1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4 - 64, (0 + GetGraphSize(clearTextTextruehandle3_).y / 4) + 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle4_, TRUE);
				}
				else if (nextStageSelect_ == 1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F((WIN_WIDTH - WIN_WIDTH / 4) - 64, (0 + GetGraphSize(clearTextTextruehandle2_).y / 4) + 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle4_, TRUE);
				}
				else
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle2_).y / 4, GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, 0 + GetGraphSize(clearTextTextruehandle3_).y / 4, GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
				}
			}
			else//真ん中
			{
				if (nextStageSelect_ == -1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4 - 64, Water::GetInstance()->GetHorizontal() - 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle4_, TRUE);
				}
				else if (nextStageSelect_ == 1)
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, SelectClearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
					DrawRotaGraph3F((WIN_WIDTH - WIN_WIDTH / 4) - 64, Water::GetInstance()->GetHorizontal() - 96, 0, 0, 1, 1, 0, SelectClearTextTextruehandle4_, TRUE);
				}
				else
				{
					DrawRotaGraph3F(WIN_WIDTH - WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle2_).x / 2, GetGraphSize(clearTextTextruehandle2_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle2_, TRUE);
					DrawRotaGraph3F(WIN_WIDTH / 4, Water::GetInstance()->GetHorizontal(), GetGraphSize(clearTextTextruehandle3_).x / 2, GetGraphSize(clearTextTextruehandle3_).y / 2, 0.5f, 0.5f, 0, clearTextTextruehandle3_, TRUE);
				}
			}
		}
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

	addObject->GetJson(seting);

	addObject->Initialize();

	addObject->SetPos(pos);
	addObject->SetSize(size);
	addObject->SetObjectType(tag);

	stageObjUnSortData_.push_back(std::move(addObject));
}

void StageManager::ChengeTag(const std::list<std::shared_ptr<Object>>::iterator& chengeData, ObjectType tag)
{
	std::shared_ptr<Object> addObject = SelectObject(tag);

	if (chengeData->get()->GetObjectType() != ObjectType::KEY && tag == ObjectType::KEY)
	{
		KeyNum_++;
	}
	else if (chengeData->get()->GetObjectType() == ObjectType::KEY && tag != ObjectType::KEY)
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
	//一応書いてるけど下の関数の中で読んでるからたぶん問題ないはず
	CollisionManager::GetInstance()->AllDelete();
	LoadStageObjectFile(stageFileName_[selectNum]);
	nowLevelNum_ = selectNum;
}

void StageManager::NextLevelLoad()
{
	if (nowLevelNum_ + 1 > stageFileName_.size() - 1)
	{
		SceneManager::GetInstance()->ChangeScene("STAGESELECT");
		return;
	}

	CollisionManager::GetInstance()->AllDelete();
	SceneManager::GetInstance()->ChangeScene("GAME", "LoadLevelName");
	LoadStageObjectFile(stageFileName_[nowLevelNum_ + 1]);
	nowLevelNum_ = nowLevelNum_ + 1;
}

void StageManager::NowStageReset()
{
	CollisionManager::GetInstance()->AllDelete();
	KeyNum_ = 0;
	LoadStageObjectFile(stageFileName_[nowLevelNum_]);
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

std::shared_ptr<Object> StageManager::TestSaveSelectObject(Object object)
{
	std::shared_ptr<Object> addObject;
	std::unique_ptr<Object> uniObj = std::make_unique<Object>(object);
	switch (object.GetObjectType())
	{

	case ObjectType::PLAYER:
		addObject = std::move(uniObj);
		addObject = std::make_shared<Player>();
		addObject->Initialize();
		break;
	case ObjectType::SPONGE_BLOCK:
		addObject = std::make_shared<SpongeBlock>();

		break;

	case ObjectType::FLOAT_BLOCK:
		addObject = std::make_shared<LevitationBlock>();

		break;

	case ObjectType::NOT_FLOAT_BLOCK:
		addObject = std::make_shared<Block>();

		break;

	case ObjectType::BREAK_BLOCK:
		addObject = std::make_shared<BreakBlock>();

		break;
	case ObjectType::GOAL:
		addObject = std::make_shared<Goal>();

		break;
	case ObjectType::KEY:
		addObject = std::make_shared<Key>();

		break;
	case ObjectType::DRAIN:
		addObject = std::make_shared<Drain>();

		break;
	case ObjectType::TUTORIAL:
		addObject = std::make_shared<TutorialObject>();

		break;
	default:
		break;

	}

	addObject = std::move(uniObj);

	return addObject;
}

void StageManager::NextSelect(bool selectReturn)
{
	isNextLoad_ = true;
	if (!selectReturn)
	{
		//次のステージへ
		NextLevelLoad();
		isClear_ = false;
		easingFrame_ = 0;
		clearTextSize_ = 0;
	}
	else
	{
		isClear_ = false;
		easingFrame_ = 0;
		clearTextSize_ = 0;
		//セレクト画面へ
		SceneManager::GetInstance()->ChangeScene("STAGESELECT");

	}

}

Vector2 StageManager::GetGraphSize(int32_t GraphHandle)
{

	float x = 0;
	float y = 0;

	GetGraphSizeF(GraphHandle, &x, &y);

	return { x,y };

}

InputLevelData StageManager::WindowsOpenLevelFileToStageManager()
{

	InputLevelData output = ImportLevel::GetInstance()->WindowsOpenLevelFile();

	if (output.isLoad)
	{
		nowLevelStageName_ = output.LevelName_;
	}

	return output;

}