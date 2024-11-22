#include "LevitationBlock.h"
#include "CollisionManager.h"
#include "Input.h"
#include "Water.h"
#include "TextureManager.h"
#include "Window.h"
#include <cmath>
#include <DxLib.h>

void LevitationBlock::Initialize()
{
	// 初期値
	pos_ = { 100.0f,640.0f };
	size_ = { 64.0f,64.0f };
	gravity_ = 10.0f;

	objectType_ = ObjectType::FLOAT_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\FloatBlook.png");
}

void LevitationBlock::Update()
{
	ObjectUpdate();

	waterSurface_ = Water::GetInstance()->GetHorizontal();

	Move();
}

void LevitationBlock::Draw()
{
	/*DrawBox(
		(int)(pos_.x - size_.x / 2.0f), (int)(pos_.y - size_.y / 2.0f),
		(int)(pos_.x + size_.x / 2.0f), (int)(pos_.y + size_.y / 2.0f),
		GetColor(255, 255, 255), TRUE);*/
	DrawGraph(pos_.x - size_.x / 2, pos_.y - size_.y / 2, textruehandle_, true);

}

void LevitationBlock::Move()
{
	// ブロックが水に浮く処理・重力
	const float distance_ = 10.0f;

	if (pos_.y < waterSurface_) {
		
		if (pos_.y <= WIN_HEIGHT - size_.y / 2) {
			pos_.y += gravity_;
		}

		if ((pos_.y - waterSurface_) >= -distance_ && (pos_.y - waterSurface_) <= distance_) {
			pos_.y = waterSurface_;
		}

	}else if(pos_.y > waterSurface_){

		if (pos_.y >= WIN_HEIGHT - WIN_HEIGHT + size_.y / 2) {
			pos_.y -= gravity_;
		}

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

void LevitationBlock::Inversion(const float easing) {
	pos_.y = easeSPos_ + easing * (easeEPos_ - easeSPos_);
	size_.y = tentSize_ * abs(easing - 0.5f) * 2;
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