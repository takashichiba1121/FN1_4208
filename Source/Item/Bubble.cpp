#include"Bubble.h"
#include"DxLib.h"

void Bubble::Initialize(const Vector2 pos) {
	position = pos;
}

void Bubble::Update(const float line) {

	position.y -= vector.y;

	if (position.y < line) {
		isDead = true;
	}
}

void Bubble::Draw() {

	DrawCircle(position.x, position.y, size.x, GetColor(255, 255, 255), false);
}