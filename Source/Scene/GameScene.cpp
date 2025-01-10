#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"Window.h"
#include"CollisionManager.h"
#include"Inversion.h"

void GameScene::Initialize()
{
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
#endif]

		Inversion::GetInstance()->Update();

		Water::GetInstance()->Update();

		StageManager::GetInstance()->Update();

		CollisionManager::GetInstance()->Update();

		if (Input::GetKeyTrigger(Input::Key::T))
		{
			isPause = true;
			pause->StartGetPause();
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
