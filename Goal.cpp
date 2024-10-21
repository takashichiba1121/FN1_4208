#include "Goal.h"
#include "Input.h"

void Goal::Initialize()
{
	pos = { 100,500 };
	size = { 32,32 };
	goal = LoadGraph("");
}

void Goal::Update()
{
	//移動(仮)
	if (Input::GetKey(Input::KEY::Left)) {
		pos.y -= speed;
	}else if (Input::GetKey(Input::KEY::Right)) {
		pos.y += speed;
	}

	//↑↓キーで水平線調節

	if (Input::GetKey(Input::KEY::Up)) {
		horizontal -= 2.0f;
	}
	if (Input::GetKey(Input::KEY::Down)) {
		horizontal += 2.0f;
	}

	//水平線より下か(上か)
	if (pos.y >= horizontal) {
		isUnderWater = true;
	}
	else {
		isUnderWater = false;
	}

	if (isUnderWater) {
		//
	}
	else {
		//
	}

	//演出(開閉時)

	

	//演出(衝突時)
	if (Input::GetKey(Input::KEY::G)) {//当たり判定
		isClear = true;
	}
	/*if (isClear == true) {
		if (a <= 4) {
			timer--;

			if (timer <= 0) {
				timer = coolTime;
				a += 0.1f;
			}
		}
	}*/

	//演出(遷移)

}

void Goal::Draw()
{
	if (isUnderWater == true) {
		//ゴール(閉)
		DrawBox(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y, GetColor(255, 255, 255), true);
	}
	else {
		//ゴール(開)
		DrawBox(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y, GetColor(0, 255, 255), true);
	}

	if (isClear) {
		//クリア
		DrawBox(1280/a, 720/a, 1280-1280/a, 720-720/a, GetColor(255, 255, 255), true);
	}
}