#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"CollisionManager.h"

void GameScene::Initialize()
{
	player = std::make_unique<Player>();
	player->Initialize();

	block = std::make_unique<Block>();
	floatBlock = std::make_unique<LevitationBlock>();
	block->Initialize();
	floatBlock->Initialize();
}

void GameScene::Update()
{
	player->Update();

	block->Update();
	floatBlock->Update();
	test.Update();

	StageManager::GetInstance()->Update();

	CollisionManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	player->Draw();

	block->Draw();
	floatBlock->Draw();

	test.Draw();
	StageManager::GetInstance()->Draw();
}

void GameScene::Finalize()
{
}
