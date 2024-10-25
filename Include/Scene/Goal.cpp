#include "Goal.h"
#include "Input.h"
#include "CollisionManager.h"

void Goal::Initialize()
{
	pos_ = { 1000.0f,200.0f };
	size_ = { 64.0f,64.0f };
	goal = LoadGraph("");
	objectType_ = ObjectType::GOAL;
	CollisionManager::GetInstance()->AddObject(this);
}

void Goal::Update()
{
	//�ړ�(��)
	/*if (Input::GetKey(Input::Key::Left)) {
		pos.y -= speed;
	}
	else if (Input::GetKey(Input::Key::Right)) {
		pos.y += speed;
	}*/

	//�����L�[�Ő���������

	if (Input::GetKey(Input::Key::Up)) {
		horizontal -= 2.0f;
	}
	if (Input::GetKey(Input::Key::Down)) {
		horizontal += 2.0f;
	}

	//��������艺��(�ォ)
	if (pos_.y+size_.y/2>= horizontal) {
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
	if (Input::GetKey(Input::Key::G)) {//�����蔻��
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
	OnCollision(this);
}

void Goal::Draw()
{
	if (isUnderWater == true) {
		//�S�[��(��)
		DrawBox(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f,
			pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f,
			GetColor(255, 255, 255), TRUE);
	}
	else {
		//�S�[��(�J)
		DrawBox(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f,
			pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f,
			GetColor(0, 255, 255), TRUE);
	}

	if (isClear) {
		//�N���A
		//DrawBox(1280 / a, 720 / a, 1280 - 1280 / a, 720 - 720 / a, GetColor(255, 255, 255), true);
		//DrawFormatString(0, 100, GetColor(0, 255, 0), "clear!!");
	}
}

void Goal::OnCollision(Object* objct)
{
	if ((pos_.y + size_.y / 2) <= (objct->GetPos().y - objct->GetSize().y / 2)) {
		DrawFormatString(0, 100, GetColor(0, 255, 0), "clear!!");
	}
	//DrawFormatString(0, 100, GetColor(0, 255, 0), "clear!!");
}
