#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"Window.h"
#include"CollisionManager.h"
#include"Inversion.h"

void GameScene::Initialize()
{
#ifdef _DEBUG
	test.Initialize();
#endif
}

void GameScene::Update()
{
#ifdef _DEBUG
	test.Update();
#endif]

	Inversion::GetInstance()->Update();

	Water::GetInstance()->Update();

	StageManager::GetInstance()->Update();

	CollisionManager::GetInstance()->Update();
}

void GameScene::Draw()
{
#ifdef _DEBUG
	test.Draw();
#endif
	StageManager::GetInstance()->Draw();

	Water::GetInstance()->Draw();
}

void GameScene::Finalize()
{
	CollisionManager::GetInstance()->AllDelete();
}
