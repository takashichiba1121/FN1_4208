#include "BreakBlock.h"
#include "Water.h"
#include "CollisionManager.h"
#include "Input.h"
#include "TextureManager.h"
#include <cmath>
#include <DxLib.h>
#include <random>
#include <iostream>

void BreakBlock::Initialize()
{
	pos_ = { 300.0f,300.0f };
	size_ = { 64.0f,64.0f };

	// 当たり判定
	objectType_ = ObjectType::BREAK_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);

	// 画像読み込み
	hpLowTexturehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\BreakBlockHpLow.png");
	hpMaxTexturehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\BreakBlockHpMax.png");
}

void BreakBlock::Update()
{
	ObjectUpdate();

	if (blockHp_ == BLOCK_HP_LOW) {
		ShakeActive();
	}
}

void BreakBlock::Draw()
{
	// ブロックのHPの段階ごとの処理
	switch (blockHp_) 
	{
	case BLOCK_BROKEN:

		isCollision_ = false;

		break;

	case BLOCK_HP_LOW:

		DrawRotaGraph3F(pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f, 
			size_.x / 64.0, size_.y / 64.0, 0.0, hpLowTexturehandle_, true);

		break;

	case BLOCK_HP_MAX:

		DrawRotaGraph3F(pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f, 
			size_.x / 64.0, size_.y / 64.0, 0.0, hpMaxTexturehandle_, true);
		
		break;
	}
}

void BreakBlock::Shake()
{
	shakeTime_++;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> rand(shakeMin_, shakeMax_);

	defaultPosition_ = pos_;
	shakePos_ = { rand(mt) / shakeMd_.x, rand(mt) / shakeMd_.y };

	if (shakeTime_ >= defaultTime_ && shakeTime_ < shakeMaxTime_) {
		pos_ += shakePos_;
	}
	if (shakeTime_ >= shakeMaxTime_) {
		shakeTime_ = defaultTime_;
		pos_ = defaultPosition_;
	}
}

void BreakBlock::ShakeActive()
{
	time_++;

	if (isShake_) {
		Shake();
	}

	if (time_ <= shakeMaxTime_) {
		isShake_ = true;
	}else {
		isShake_ = false;
	}
}

void BreakBlock::Damage()
{
	blockHp_ -= damageValue_;
}

void BreakBlock::OnCollision(Object* object)
{
	if (object->GetObjectType() == ObjectType::PLAYER &&
		pos_.y >= (object->GetPos().y + object->GetSize().y / 2)) {
		Damage();
	}
}