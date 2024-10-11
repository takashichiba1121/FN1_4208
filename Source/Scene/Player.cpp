#include "Player.h"
#include "Input.h"
#include "DxLib.h"

void Player::Initialize() {
	pos = { 100,100 };
}

void Player::Update() {

	Operation();

	if (pos.y >= horizontal) {
		isUnderWater = true;
	}
	else {
		isUnderWater = false;
	}

	//�n��Ɛ����ŃX�s�[�h��ς���
	if (isUnderWater) {
		speed = waterSpeed;
	}
	else {
		speed = groundSpeed;
	}

	//�W�����v�ɂ���ċ󒆂ɂ���Ƃ��̏���
	if (!isOnFloor) {

		//�v���C���[���W�ɏd�͂����Z
		pos.y += gravity;	//gravity�̏����l�̓}�C�i�X�̂��ߍŏ��͏�����ɓ���

		//�������x�����X�ɏグ��(�������͔���)
		gravity += 1.0f / (isUnderWater + 1);

		//�������x�̏�������߂�(�������͔���)
		if (gravity >= MaxGravity / (isUnderWater + 1)) {
			gravity = MaxGravity / (isUnderWater + 1);
		}

		//�����ł���Ζ����W�����v�\
		if (isUnderWater) {
			isCanJump = true;
		}
		else {
			isCanJump = false;
		}
	}
	else {
		isCanJump = true;
	}

	//�E�B���h�E�̈�ԉ��Ŏ~�܂�
	if (pos.y >= 720 - size.y / 2) {
		pos.y = 720 - size.y / 2;
		isOnFloor = true;
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

}

//���ړ�
void Player::Move() {
	if (Input::GetKey(Input::KEY::A)) {
		pos.x -= speed;
	}
	if (Input::GetKey(Input::KEY::D)) {
		pos.x += speed;
	}
}

//�W�����v
void Player::Jump() {
	if (Input::GetKeyTrigger(Input::KEY::Space) && isCanJump) {
		isOnFloor = false;

		//�W�����v�̏���(�������͔���)
		gravity = InitJumpVelocity / (isUnderWater + 1);
	}
}

void Player::Draw() {

	DrawBox(
		(int)(pos.x - size.x / 2), (int)(pos.y - size.x / 2),
		(int)(pos.x + size.x / 2), (int)(pos.y + size.x / 2),
		GetColor(250, 250, 250), true);

	DrawLine(0, horizontal, 1280, horizontal, GetColor(255, 255, 255));
	DrawFormatString(0, 0, GetColor(255, 255, 255), "horizontal : %f (�����L�[�Œ���)", horizontal);
}