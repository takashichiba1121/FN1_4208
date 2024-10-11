#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"

void GameScene::Initialize()
{
	player = std::make_unique<Player>();
	player->Initialize();
}

void GameScene::Update()
{
	player->Update();
}

void GameScene::Draw()
{
	player->Draw();
}

void GameScene::Finalize()
{
}
