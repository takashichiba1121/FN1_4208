#include <DxLib.h>
#include "Drain.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "Water.h"
#include "Inversion.h"

void Drain::Initialize() {
	objectType_ = ObjectType::DRAIN;
	isExclude_ = false;
	
	drainTexture = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Drain.png");
	guideTexture = TextureManager::Instance()->LoadTexture("Resources\\Texture\\GuideW.png");
	CollisionManager::GetInstance()->AddObject(this);

}

void Drain::Update() {

	const float MaxTrans = 255.0f;

	if (Inversion::GetInstance()->GetIsInversion() ||
		Water::GetInstance()->GetIsChangeHorizontal() ||
		Water::GetInstance()->GetHorizontal() == pos_.y) {
		drawGuide = false;
	}
	
	if (drawGuide && guideTrans < MaxTrans) {
		guideTrans += MaxTrans / 10.0f;
	}

	if (!drawGuide && guideTrans > 0) {
		guideTrans -= MaxTrans / 10.0f;
	}

	ObjectUpdate();
	drawGuide = false;
}

void Drain::Draw() {

	DrawExtendGraph(pos_.x - size_.x / 2, pos_.y - size_.y / 2,pos_.x + size_.x / 2, pos_.y + size_.y / 2,
		drainTexture, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, guideTrans);
	DrawExtendGraph(
		pos_.x - size_.x / 2, pos_.y - size_.y * 1.5f,
		pos_.x + size_.x / 2, pos_.y - size_.y / 2,
		guideTexture, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Drain::OnCollision(Object* objct) {

	if (objct->GetObjectType() == ObjectType::PLAYER) {
		drawGuide = true;
	}
}

void Drain::Inversion(const float easing) {
	pos_.y = easeSPos_ + easing * (easeEPos_ - easeSPos_);
	size_.y = tentSize_ * abs(easing - 0.5f) * 2;
}