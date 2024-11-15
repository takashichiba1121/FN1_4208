#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"Window.h"
#include"CollisionManager.h"
#include"Inversion.h"

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

	spongeBlock = std::make_unique<SpongeBlock>();
	spongeBlock->Initialize();

	test.Initialize();
}

void GameScene::Update()
{
	player->Update();

	block->Update();
	floatBlock->Update();
	breakBlock->Update();
	spongeBlock->Update();

	goal->Update();
	test.Update();

	Inversion::GetInstance()->Update();

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
	spongeBlock->Draw();

	goal->Draw();
	test.Draw();
	StageManager::GetInstance()->Draw();

	Water::GetInstance()->Draw();
}

void GameScene::Finalize()
{
}
