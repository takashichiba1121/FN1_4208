#include "LevitationBlock.h"
#include "CollisionManager.h"
#include <cmath>
#include "Input.h"

void LevitationBlock::Initialize()
{
	// 初期値
	pos_ = { 640.0f,100.0f };
	size_ = { 64.0f,64.0f };
	gravity_ = 10.0f;

	objectType_ = ObjectType::FLOAT_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);
}

void LevitationBlock::Update()
{
	oldPos_ = pos_;

	waterSurface_ = Water::GetInstance()->GetHorizontal();

	Move();
}

void LevitationBlock::Draw()
{
	DrawBox(
		pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f,
		pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f,
		GetColor(255, 255, 255), TRUE);
}

void LevitationBlock::Move()
{
	// ブロックが水に浮く処理・重力
	if (pos_.y < waterSurface_ + 10) {
		
		const float distance_ = 10.0f;
		pos_.y += gravity_;

		if ((pos_.y - waterSurface_) >= -distance_ && (pos_.y - waterSurface_) <= distance_) {
			pos_.y = waterSurface_;
		}
	}
	if(pos_.y > waterSurface_ + 10){
		
		const float distance_ = 10.0f;

		pos_.y -= gravity_;

		if ((pos_.y - waterSurface_) >= -distance_ && (pos_.y - waterSurface_) <= distance_) {
			pos_.y = waterSurface_; 
		}
	}
	if (pos_.y == waterSurface_) {
		isEasing_ = true;
	}
	if (isEasing_) {
		frame_++;
		//pos_.y = EaseInOutBackP(frame_, waterSurface_, difference_, easingTime_);

		if (frame_ >= maxFrame_) {
			frame_ = 0;
			isEasing_ = false;
		}
	}
}

float LevitationBlock::EaseInOutBackP(float t, float b, float c, float d)
{
	float x = t / d;
	float v = EaseInOutBack(x);
	float result = v * c + b;

	return result;
}

float LevitationBlock::EaseInOutBack(float x)
{
	const float c1 = 1.7f;
	const float c2 = c1 * 1.5f;

	return static_cast<float>(x < 0.5
		? (std::pow(2.0f * x, 2.0f) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f
		: (std::pow(2.0f * x - 2.0f, 2.0f) * ((c2 + 1.0f) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f);
}