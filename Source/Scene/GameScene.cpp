#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"Window.h"
#include"CollisionManager.h"

void GameScene::Initialize()
{
	player = std::make_unique<Player>();
	player->Initialize();

}

void GameScene::Update()
{
	player->Update();

	Inversion::GetInstance()->Update();
	test.Update();

	

	Water::GetInstance()->Update();

	StageManager::GetInstance()->Update();

	CollisionManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	player->Draw();

	test.Draw();
	StageManager::GetInstance()->Draw();

	Water::GetInstance()->Draw();
}

void GameScene::Finalize()
{
}
