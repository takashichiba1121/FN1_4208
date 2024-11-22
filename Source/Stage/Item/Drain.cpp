#include <DxLib.h>
#include "Drain.h"
#include "CollisionManager.h"

void Drain::Initialize() {
	objectType_ = ObjectType::DRAIN;
	isExclude_ = false;
	size_ = { 64,64 };
	CollisionManager::GetInstance()->AddObject(this);
}

void Drain::Update() {
	ObjectUpdate();

	color = GetColor(0, 255, 0);
}

void Drain::Draw() {
	DrawCircle(pos_.x, pos_.y, size_.x / 2, color, true);
}

void Drain::OnCollision(Object* objct) {

	if (objct->GetObjectType() == ObjectType::PLAYER) {
		color = GetColor(0, 200, 100);
	}
}

void Drain::Inversion(const float easing) {
	pos_.y = easeSPos_ + easing * (easeEPos_ - easeSPos_);
	size_.y = tentSize_ * abs(easing - 0.5f) * 2;
}