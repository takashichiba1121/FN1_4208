#include "Confetti.h"
#include"DxLib.h"
#include"CollisionManager.h"
#include"Random.h"

Confetti::~Confetti()
{
}

void Confetti::Initialize()
{
	colorR = Random::RandomFloat(100, 250);
	colorG = Random::RandomFloat(100, 250);
	colorB = Random::RandomFloat(100, 250);
	pos = Random::RandomFloat(0.0f, 1400.0f);
	pos_ = { pos,10 };
	size = Random::RandomFloat(8.0f, 18.0f);
	size_ = { size,size };
	isExclude_ = false;

	objectType_ = ObjectType::NONE;
	CollisionManager::GetInstance()->RemoveObject(this);
}

void Confetti::Update()
{
	//ゴール時の紙吹雪
	//移動量をランダム化
	pos_.x += Random::RandomFloat(-4.0f, 1.0f);
	pos_.y += vector.y + Random::RandomFloat(-1.0f, 1.0f);

	//一定値まで行くと消滅
	if (pos_.y > 800) {
		isDead = true;
	}
}

void Confetti::Draw()
{
	//DrawCircle((int)pos_.x, (int)pos_.y, (int)size, GetColor(colorR, colorG, colorB), true);
	DrawBox(
		(int)(pos_.x - size_.x / 2), (int)(pos_.y - size_.y / 2),
		(int)(pos_.x + size_.x / 2), (int)(pos_.y + size_.y / 2),
		GetColor(colorR, colorG, colorB), true);
}

void Confetti::OnCollision(Object* objct)
{
}
