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
	//�ړ�(��)
	if (Input::GetKey(Input::KEY::Left)) {
		pos.y -= speed;
	}else if (Input::GetKey(Input::KEY::Right)) {
		pos.y += speed;
	}

	//�����L�[�Ő���������

	if (Input::GetKey(Input::KEY::Up)) {
		horizontal -= 2.0f;
	}
	if (Input::GetKey(Input::KEY::Down)) {
		horizontal += 2.0f;
	}

	//��������艺��(�ォ)
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

	//���o(�J��)

	

	//���o(�Փˎ�)
	if (Input::GetKey(Input::KEY::G)) {//�����蔻��
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

	//���o(�J��)

}

void Goal::Draw()
{
	if (isUnderWater == true) {
		//�S�[��(��)
		DrawBox(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y, GetColor(255, 255, 255), true);
	}
	else {
		//�S�[��(�J)
		DrawBox(pos.x - size.x, pos.y - size.y, pos.x + size.x, pos.y + size.y, GetColor(0, 255, 255), true);
	}

	if (isClear) {
		//�N���A
		DrawBox(1280/a, 720/a, 1280-1280/a, 720-720/a, GetColor(255, 255, 255), true);
	}
}