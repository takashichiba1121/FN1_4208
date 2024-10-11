#include "Player.h"
#include "Input.h"
#include "DxLib.h"
#include <random>

void Player::Initialize() {

	pos_ = { 100,100 };
	objectType = ObjectType::PLAYER;
}

void Player::Update() {

	Operation();

	//��������n��ɏオ��邩����
	if (gravity <= 0 && pos_.y <= horizontal && isUnderWater) {
		canCrawlUp = true;
		pos_.y = horizontal;
	}
	else {
		canCrawlUp = false;
	}

	//���ʂ̏ォ�����𔻒�(��)
	if (pos_.y >= horizontal) {
		isUnderWater = true;
	}
	else {
		isUnderWater = false;
	}

	//�n��Ɛ����ŃX�s�[�h��ς���
	if (isUnderWater) {
		speed = WaterSpeed;
	}
	else {
		speed = GroundSpeed;
	}

	//�W�����v�ɂ���ċ󒆂ɂ���Ƃ��̏���
	if (!isOnFloor) {

		//�v���C���[���W�ɏd�͂����Z
		pos_.y += gravity;	//gravity�̏����l�̓}�C�i�X�̂��ߍŏ��͏�����ɓ���

		//�������x�����X�ɏグ��(�������͔���)
		gravity += 1.0f / (isUnderWater + 1);

		//�������x�̏�������߂�(�������͔���)
		if (gravity >= MaxGravity / (isUnderWater + 1)) {
			gravity = MaxGravity / (isUnderWater + 1);
		}

		//�����ł���Ζ����W�����v�\
		if (isUnderWater) {
			canJump = true;
		}
		else {
			canJump = false;
		}
	}
	else {
		canJump = true;
	}

	//��ʂŎ~�܂�(��)
	if (pos_.y >= underLine - size_.y / 2) {
		pos_.y = underLine - size_.y / 2;
		isOnFloor = true;
	}
	else {
		isOnFloor = false;
	}
	
}

//�L�[���͂ő���ł��鏈��
void Player::Operation() {

	Move();
	Jump();

	//�����L�[�Ő���������	
	if (Input::GetKey(Input::KEY::Up)) {
		horizontal -= 2.0f;
	}
	if (Input::GetKey(Input::KEY::Down)) {
		horizontal += 2.0f;
	}

	//�����L�[�Œ�ʒ���
	if (Input::GetKey(Input::KEY::Left)) {
		underLine -= 2.0f;
	}
	if (Input::GetKey(Input::KEY::Right)) {
		underLine += 2.0f;
	}

	if (Input::GetKeyTrigger(Input::KEY::R)) {
		pos_ = { 100,100 };
	}
}

//���ړ�
void Player::Move() {
	if (Input::GetKey(Input::KEY::A)) {
		pos_.x -= speed;
	}
	if (Input::GetKey(Input::KEY::D)) {
		pos_.x += speed;
	}
}

//�W�����v
void Player::Jump() {
	if (Input::GetKeyTrigger(Input::KEY::Space) && canJump) {
		isOnFloor = false;

		//��������n��ɏオ��Ƃ��͒n��Ɠ����悤�ȃW�����v(�������)
		if (canCrawlUp) {
			isUnderWater = false;
			initJumpVelocity = -MaxGravity / 1.25f;
		}
		else {
			initJumpVelocity = -MaxGravity;
		}

		//�W�����v�̏���(�������͔���)
		gravity = initJumpVelocity / (isUnderWater + 1);

	}
}

void Player::Draw() {

	DrawBox(
		(int)(pos_.x - size_.x / 2), (int)(pos_.y - size_.y / 2),
		(int)(pos_.x + size_.x / 2), (int)(pos_.y + size_.y / 2),
		GetColor(250, 250, 250), true);

	DrawLine(0, (int)horizontal, 1280, (int)horizontal, GetColor(100, 255, 255));
	DrawLine(0, (int)underLine, 1280, (int)underLine, GetColor(255, 255, 255));
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "horizontal : %f (�����L�[�Œ���)", horizontal);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "underLine : %f (�����L�[�Œ���)", underLine);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "isUnderWater : %d", isUnderWater);
}

void Player::OnCollision(Object objct) {
	
}