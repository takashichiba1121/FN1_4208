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

	objectType_ = ObjectType::BREAK_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);
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
	switch (blockHp_) 
	{
	case BLOCK_BROKEN:

		break;

	case BLOCK_HP_LOW:

		DrawBox(
			(int)(pos_.x - size_.x / 2.0f), (int)(pos_.y - size_.y / 2.0f),
			(int)(pos_.x + size_.x / 2.0f), (int)(pos_.y + size_.y / 2.0f),
			GetColor(255, 0, 0), TRUE);

		break;

	case BLOCK_HP_MAX:

		DrawBox(
			(int)(pos_.x - size_.x / 2.0f), (int)(pos_.y - size_.y / 2.0f),
			(int)(pos_.x + size_.x / 2.0f), (int)(pos_.y + size_.y / 2.0f),
			GetColor(0, 255, 0), TRUE);
		
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

	if (shakeTime_ >= defaultTime_) {
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
}
