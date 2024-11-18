#include "Block.h"
#include "CollisionManager.h"
#include <DxLib.h>
#include <cmath>

void Block::Initialize()
{
	// ‰Šú’l
	pos_ = { 640.0f,688.0f };
	size_ = { 64.0f,64.0f };

	objectType_ = ObjectType::NOT_FLOAT_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);
}

void Block::Update()
{
	oldPos_ = pos_;
}

void Block::Draw()
{
	DrawBox(
		(int)(pos_.x - size_.x / 2.0f), (int)(pos_.y - size_.y / 2.0f),
		(int)(pos_.x + size_.x / 2.0f), (int)(pos_.y + size_.y / 2.0f),
		GetColor(255, 255, 255), TRUE);
}