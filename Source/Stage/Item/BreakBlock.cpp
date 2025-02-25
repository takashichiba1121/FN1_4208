#include "BreakBlock.h"
#include "Water.h"
#include "CollisionManager.h"
#include "Input.h"
#include "Inversion.h"
#include "TextureManager.h"
#include "SoundPlayManager.h"
#include <cmath>
#include <DxLib.h>
#include <random>
#include <iostream>

void BreakBlock::Initialize()
{
	
	// 当たり判定
	objectType_ = ObjectType::BREAK_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);
	
	// 画像読み込み
	hpLowTextureHandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\BreakBlockHpLow.png");
	hpMaxTextureHandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\BreakBlockHpMax.png");

	// アニメーション画像読み込み
	LoadDivGraph("Resources\\Texture\\BreakBlockAnimation.png", maxFrame, maxFrame, 1, 64, 64, animationImage);
}

void BreakBlock::Update()
{
	ObjectUpdate();
	
	switch(blockHp_)
	{
	case BLOCK_BROKEN:

		isCollision_ = false;

		break;

	case BLOCK_HP_LOW:

		// アニメーション処理
		animationFrameAdjust++;

		if (animationFrameAdjust == animationSpeed_) {
			animationFrame++;
			animationFrameAdjust = 0;
		}
		if (animationFrame == maxFrame) {
			blockHp_ = BLOCK_BROKEN;
			isCollision_ = false;
			animationFrame = 0;
		}

		break;

	case BLOCK_HP_MAX:
		
		break;
	}
}

void BreakBlock::Draw()
{
	// ブロックHPの段階ごとの処理
	switch (blockHp_) 
	{
	case BLOCK_BROKEN:

		break;
		
	case BLOCK_HP_LOW:

		// アニメーションブロック描画
		DrawExtendGraph(
			(int)(((pos_.x - size_.x / 2.0f) - (size_.x / 64.0f)) + shakePos_.x), (int)(((pos_.y - size_.y / 2.0f) - (size_.y / 64.0f)) + shakePos_.y),
			(int)(((pos_.x + size_.x / 2.0f) + (size_.x / 64.0f)) + shakePos_.x), (int)(((pos_.y + size_.y / 2.0f) + (size_.y / 64.0f)) + shakePos_.y),
			animationImage[animationFrame], true);

		break;

	case BLOCK_HP_MAX:

		DrawExtendGraph(
			(int)(((pos_.x - size_.x / 2.0f) - (size_.x / 64.0f)) + shakePos_.x),
			(int)(((pos_.y - size_.y / 2.0f) - (size_.y / 64.0f)) + shakePos_.y),
			(int)(((pos_.x + size_.x / 2.0f) + (size_.x / 64.0f)) + shakePos_.x),
			(int)(((pos_.y + size_.y / 2.0f) + (size_.y / 64.0f)) + shakePos_.y),
			animationImage[animationFrame], true);
		
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
		//pos_ += shakePos_;
	}
	if (shakeTime_ >= shakeMaxTime_) {
		shakeTime_ = defaultTime_;
		pos_ = defaultPosition_;
		shakePos_ = { 0,0 };
	}
}

void BreakBlock::ShakeActive()
{
	time_++;

	if (time_ <= shakeMaxTime_) {
		Shake();
	}
}

void BreakBlock::Damage()
{
	blockHp_ = damageValue_;
	SoundPlayManager::Instance()->SoundPlay(SoundPlayManager::Instance()->GetSound().block_break);
}

void BreakBlock::OnCollision(Object* object)
{
	if (object->GetObjectType() == ObjectType::PLAYER &&
		pos_.y >= (object->GetPos().y + object->GetSize().y / 2)) {
		if (!Inversion::GetInstance()->GetIsInversion() && !Inversion::GetInstance()->GetEndInversion()) {
			Damage();
		}
	}
}

void BreakBlock::Inversion(const float easing) {
	pos_.y = easeSPos_ + easing * (easeEPos_ - easeSPos_);
	size_.y = tentSize_ * abs(easing - 0.5f) * 2;
}