#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"Window.h"
#include"CollisionManager.h"
#include"Inversion.h"

void GameScene::Initialize()
{
	pause_ = std::make_unique<Pause>();

	pause_->Initialize();

#ifdef _DEBUG
	test.Initialize();
#endif
}

void GameScene::Update()
{
	if (isPause==false)
	{

#ifdef _DEBUG
	test.Update();
#endif
	pause_->InGameUpdate();

		Inversion::GetInstance()->Update();

		Water::GetInstance()->Update();

		StageManager::GetInstance()->Update();

		CollisionManager::GetInstance()->Update();

		//パットはYボタン
		if (Input::GetKeyTrigger(Input::Key::R)|| Input::TriggerPadKey(PAD_INPUT_4))
		{
			StageManager::GetInstance()->NowStageReset();
		}

		//パットはStartだかoptionボタン
		if (Input::GetKeyTrigger(Input::Key::T)|| Input::TriggerPadKey(PAD_INPUT_8))
		{
			isPause = true;
			pause_->StartGetPause();
		}

	}
	else
	{
		pause_->Update();

		if (pause_->IsEndGetPause())
		{
			isPause = false;
		}
	}
}

void GameScene::Draw()
{
#ifdef _DEBUG
	test.Draw();
#endif
	StageManager::GetInstance()->Draw();

	Water::GetInstance()->Draw();

	if (isPause)
	{
		pause_->Draw();
	}
	else
	{
		pause_->InGameDraw();
	}
}

void GameScene::Finalize()
{
	CollisionManager::GetInstance()->AllDelete();
}
