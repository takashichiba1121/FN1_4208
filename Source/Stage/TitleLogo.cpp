#include "TitleLogo.h"
#include "TextureManager.h"
#include "Water.h"
#include "Random.h"
#include <DxLib.h>

void TitleLogo::Initialize(const int num) {

	frame = Random::RandomFloat(0,frameMax);

	size_ = { 256,256 };
	pos_ = { 320,320 };
	sheetNum = num;
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\title.png");

}

void TitleLogo::Update() {
	if (frame >= frameMax) {
		updown = false;
	}
	else if (frame <= 0) {
		updown = true;
	}

	if (updown) {
		frame++;
	}
	else {
		frame--;
	}

	easepos_ = pos_.y + EaseInOut(frame / frameMax) * 30.0f;
}

void TitleLogo::Draw() {
	DrawRectExtendGraph(
		pos_.x - size_.x / 2, easepos_ - size_.y / 2, pos_.x + size_.x / 2, easepos_ + size_.y / 2,
		textureSize.x * sheetNum, 0, textureSize.x, textureSize.y, textruehandle_, true);

}