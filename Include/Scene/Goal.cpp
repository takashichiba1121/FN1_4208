#include "Goal.h"
#include "Input.h"
#include "CollisionManager.h"
#include <random>

void Goal::Initialize()
{
	pos_ = { 1000.0f,200.0f };
	size_ = { 64.0f,64.0f };
	goal = LoadGraph("");
	objectType_ = ObjectType::GOAL;
	CollisionManager::GetInstance()->AddObject(this);

	isLock = true;
}

void Goal::Update()
{
	horizontal = Water::GetInstance()->GetHorizontal();

	//�{���`�F�b�N
	if (Input::GetKey(Input::Key::Up)) {
		//keydata->isLock=true;
		isLock = true;
	}
	else if (Input::GetKey(Input::Key::Down)) {
		isLock = false;
	}

	/*if (key != 1) {
		isLock = true;
	}*/

	//��������艺��(�ォ)
	if (pos_.y + size_.y / 2 >= horizontal) {
		isUnderWater = true;
	}
	else {
		isUnderWater = false;
	}

	if (isUnderWater) {
		//�S�[��(��)
		isCollision_ = true;
	}
	/*else if (isUnderWater == false && isClear == false) {
		isCollision_ = true;
	}*/
	else {
		//�S�[��(�J)
		isCollision_ = true;
	}

	//���o(�J��)



	//���o(�Փˎ�)
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
	if (isClear) {

	}
}

void Goal::Inversion() {
	pos_ = {
		pos_.x,
		WIN_HEIGHT / 2 + (WIN_HEIGHT / 2 - pos_.y)
	};
}

void Goal::Draw()
{
	if (isUnderWater == false && isLock == true || isUnderWater == true && isLock==true) {
		//�S�[��(�������)
		DrawBox(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f,
			pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f,
			GetColor(255, 0, 0), TRUE);
		DrawFormatString(pos_.x - 15, pos_.y - 10, GetColor(0, 0, 0), "Goal");
	}
	else if (isUnderWater) {
		//�S�[��(��)
		DrawBox(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f,
			pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f,
			GetColor(255, 255, 255), TRUE);
		DrawFormatString(pos_.x - 15, pos_.y - 10, GetColor(0, 0, 0), "Goal");
	}
	else {
		//�S�[��(�J)
		DrawBox(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f,
			pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f,
			GetColor(0, 255, 255), TRUE);
		DrawFormatString(pos_.x - 15, pos_.y - 10, GetColor(0, 0, 0), "Goal");
	}

	if (isClear) {
		//�N���A
		//DrawBox(1280 / a, 720 / a, 1280 - 1280 / a, 720 - 720 / a, GetColor(255, 255, 255), true);
		//DrawFormatString(0, 100, GetColor(0, 255, 0), "clear!!");
	}
}

void Goal::OnCollision(Object* objct)
{
	if (objct->GetObjectType() == ObjectType::PLAYER && isUnderWater == false && isLock == false) {
		DrawFormatString(0, 100, GetColor(0, 255, 0), "clear!!");
		isClear = true;
	}
}