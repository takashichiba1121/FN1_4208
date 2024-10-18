#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"

void GameScene::Initialize()
{
	player = new Player();
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
}

void GameScene::Draw()
{
	player->Draw();

	block->Draw();
	floatBlock->Draw();
}

void GameScene::Finalize()
{
}
