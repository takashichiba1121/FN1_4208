#include "BreakBlock.h"
#include "Water.h"
#include "CollisionManager.h"
#include <cmath>
#include <DxLib.h>
#include <random>

void BreakBlock::Initialize()
{
	pos_ = { 300.0f,200.0f };
	size_ = { 64.0f,64.0f };
}

void BreakBlock::Update()
{
	switch (blockHp_) 
	{
	case BlockBroken:

		Shake();
		
		break;

	case BlockHpLow:

		Shake();

		break;

	case BlockHpMax:

		Shake();

		break;
	}
}

void BreakBlock::Draw()
{
	switch (blockHp_) 
	{
	case BlockBroken:

		break;

	case BlockHpLow:

		DrawBox(
			(int)(pos_.x - size_.x / 2.0f), (int)(pos_.y - size_.y / 2.0f),
			(int)(pos_.x + size_.x / 2.0f), (int)(pos_.y + size_.y / 2.0f),
			GetColor(255, 0, 255), TRUE);
		break;

	case BlockHpMax:

		DrawBox(
			(int)(pos_.x - size_.x / 2.0f), (int)(pos_.y - size_.y / 2.0f),
			(int)(pos_.x + size_.x / 2.0f), (int)(pos_.y - size_.y / 2.0f),
			GetColor(255, 255, 255), TRUE);

		break;
	}
}

void BreakBlock::Shake()
{
	shakeTime_++;

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand(shakeMin_, shakeMax_);

	defaultPosition_ = pos_.x;
	shakePosX_ = rand(mt) / shakeMdX_;

	if (shakeTime_ >= 0) {
		pos_.x += shakePosX_;
	}
	if (shakeTime_ >= shakeMaxTime_) {
		shakeTime_ = 0;
		pos_.x = defaultPosition_;
	}
}