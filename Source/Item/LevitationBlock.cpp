#include "LevitationBlock.h"
#include "CollisionManager.h"
#include <cmath>

void LevitationBlock::Initialize()
{
	// 初期値
	pos_ = { 640.0f,100.0f };
	size_ = { 64.0f,64.0f };
	gravity_ = 10.0f;

	CollisionManager::GetInstance()->AddObject(this);
}

void LevitationBlock::Update()
{
	// ブロックが水に浮く処理
	if (pos_.y < 360) {
		pos_.y += gravity_;
	}
	if (pos_.y == 360) {
		frame_++;
		pos_.y += EaseInOutBackP(frame_, 0, 100, 60);
	}
}

void LevitationBlock::Draw()
{
	DrawBox(
		pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f,
		pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f,
		GetColor(255, 255, 255), TRUE);
}

float LevitationBlock::EaseInOutBackP(float t, float b, float c, float d)
{
	float x = t / d;
	float v = EaseInOutBack(x);
	float result = v;

	return result;
}

float LevitationBlock::EaseInOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

	return static_cast<float>(x < 0.5
		? (std::pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
		: (std::pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2);
}