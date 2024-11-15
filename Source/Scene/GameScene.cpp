#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"Window.h"
#include"CollisionManager.h"

void GameScene::Initialize()
{
	player = std::make_unique<Player>();
	player->Initialize();

	block = std::make_unique<Block>();
	floatBlock = std::make_unique<LevitationBlock>();
	breakBlock = std::make_unique<BreakBlock>();
	block->Initialize();
	floatBlock->Initialize();
	breakBlock->Initialize();

	goal = std::make_unique<Goal>();
	goal->Initialize();

	test.Initialize();
}

void GameScene::Update()
{
	player->Update();

	block->Update();
	floatBlock->Update();
	breakBlock->Update();

	goal->Update();
	test.Update();

	Water::GetInstance()->Update();

	StageManager::GetInstance()->Update();

	CollisionManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	player->Draw();

	block->Draw();
	floatBlock->Draw();
	breakBlock->Draw();

	goal->Draw();
	test.Draw();
	StageManager::GetInstance()->Draw();

	Water::GetInstance()->Draw();
}

void GameScene::Finalize()
{
}
