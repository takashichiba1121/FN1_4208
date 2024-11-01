#include "Player.h"
#include "Input.h"
#include "DxLib.h"
#include "CollisionManager.h"
#include <random>

void Player::Initialize() {

	pos_ = { 100,100 };
	size_ = { 64,64 };

	bubbleEmitter = std::make_unique<BubbleEmitter>();
	bubbleEmitter->Initialize(20);

	objectType_ = ObjectType::PLAYER;
	CollisionManager::GetInstance()->AddObject(this);
}

void Player::Update() {

	oldPos_ = pos_;
	color = GetColor(255, 255, 255);
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
		canJumpTimer--;
		if (canJumpTimer <= 0) {
			canJump = false;
		}
		else {
			canJump = true;
		}
	}

	//�p�[�e�B�N���X�V
	bubbleEmitter->Update(pos_);
	bubbleEmitter->SetHorizontal(horizontal);

	//��ʂŎ~�܂�(��)
	if (pos_.y >= underLine - size_.y / 2) {
		pos_.y = underLine - size_.y / 2;
		canJumpTimer = canJumpTimerMax;
		canJump = true;
	}

}

//�L�[���͂ő���ł��鏈��
void Player::Operation() {

	Move();
	Jump();

	//�����L�[�Ő���������
	if (Input::GetKey(Input::Key::Up) && horizontal > 0) {
		horizontal -= 2.0f;
	}
	if (Input::GetKey(Input::Key::Down) && horizontal < 720) {
		horizontal += 2.0f;
	}

	//�����L�[�Œ�ʒ���
	if (Input::GetKey(Input::Key::Left) && underLine > 0) {
		underLine -= 2.0f;
	}
	if (Input::GetKey(Input::Key::Right) && underLine < 720) {
		underLine += 2.0f;
	}

	//�v���C���[�̈ʒu���Z�b�g
	if (Input::GetKeyTrigger(Input::Key::R)) {
		pos_ = { 100,100 };
	}
}

//���ړ�
void Player::Move() {
	if (Input::GetKey(Input::Key::A) && pos_.x - size_.x / 2 > 0) {
		pos_.x -= speed;
	}
	if (Input::GetKey(Input::Key::D) && pos_.x + size_.x / 2 < 1280) {
		pos_.x += speed;
	}
}

//�W�����v
void Player::Jump() {
	if (Input::GetKeyTrigger(Input::Key::Space) && canJump) {

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
		color, true);
	//DrawLine(0, (int)horizontal, 1280, (int)horizontal, GetColor(100, 255, 255));
	DrawLine(0, (int)underLine, 1280, (int)underLine, GetColor(255, 255, 255));

	bubbleEmitter->Draw();
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "horizontal : %f (�����L�[�Œ���)", horizontal);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "underLine : %f (�����L�[�Œ���)", underLine);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "canJump : %d", canJump);
}

void Player::OnCollision(Object* objct) {
	if ((pos_.y + size_.y / 2) <= (objct->GetPos().y - objct->GetSize().y / 2)) {
		canJumpTimer = canJumpTimerMax;
		gravity = 0.0f;
	}
}