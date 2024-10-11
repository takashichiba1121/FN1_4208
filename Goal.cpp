#include "Goal.h"

void Goal::Initialize()
{
	pos = { 100,500 };
	size = { 32,32 };
	goal = LoadGraph("");
}

void Goal::Update()
{
	/*if (isLock == false) {
		if (pos.y >= 300) {
			isLock = true;
		}
	}
	else {
		if (pos.y < 300) {
			isLock = false;
		}
	}*/
}

void Goal::Draw()
{
	if (isLock == false) {
		//ƒS[ƒ‹(•Â)
		DrawBox(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y, GetColor(255, 255, 255), true);
	}
	else {
		//ƒS[ƒ‹(ŠJ)
		DrawBox(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y, GetColor(0, 255, 255), true);
	}
}