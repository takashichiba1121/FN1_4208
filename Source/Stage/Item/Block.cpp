#include "Block.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include <DxLib.h>
#include <cmath>

void Block::Initialize()
{
	// 初期値
	pos_ = { 640.0f,688.0f };
	size_ = { 64.0f,64.0f };

	// 当たり判定
	objectType_ = ObjectType::NOT_FLOAT_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);

	// 画像読み込み
	textureHandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Block.png");
}

void Block::Update()
{
	ObjectUpdate();
}

void Block::Draw()
{
	// ブロックの描画
	DrawRotaGraph3F(
		pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f,
		(double)(size_.x / 64.0), (double)(size_.y / 64.0), 0.0, textureHandle_, true);
}

void Block::Inversion(const float easing) {
	pos_.y = easeSPos_ + easing * (easeEPos_ - easeSPos_);
	size_.y = tentSize_ * abs(easing - 0.5f) * 2;
}