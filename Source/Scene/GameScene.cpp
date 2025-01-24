#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"Window.h"
#include"CollisionManager.h"
#include"Inversion.h"

void GameScene::Initialize()
{

	soundPlayManager = SoundPlayManager::Instance();

	pause = std::make_unique<Pause>();

	pause->Initialize();

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

		Inversion::GetInstance()->Update();

		Water::GetInstance()->Update();

		StageManager::GetInstance()->Update();

		CollisionManager::GetInstance()->Update();

		//パットはYボタン
		if (Input::GetKeyTrigger(Input::Key::R)|| Input::TriggerPadKey(PAD_INPUT_4))
		{
			StageManager::GetInstance()->NowStageReset();
			soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionB, 100);
		}

		//パットはStartだかoptionボタン
		if (Input::GetKeyTrigger(Input::Key::T)|| Input::TriggerPadKey(PAD_INPUT_8))
		{
			isPause = true;
			pause->StartGetPause();
			soundPlayManager->SoundPlay(soundPlayManager->GetSound().waterA, 100);
		}

	}
	else
	{
		pause->Update();

		if (pause->IsEndGetPause())
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
		pause->Draw();
	}
}

void GameScene::Finalize()
{
	CollisionManager::GetInstance()->AllDelete();
}
