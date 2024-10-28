#include "Splash.h"
#include"DxLib.h"
#include"Random.h"

void Splash::Initialize(const Vector2 pos) {
	position = pos;
}

void Splash::Update(const float line) {

	deathTimer--;
	if (deathTimer <= 0) {
		isDead = true;
	}
}

void Splash::Draw() {
	DrawCircle((int)position.x, (int)position.y, (int)size, GetColor(100, 255, 255), true);
}