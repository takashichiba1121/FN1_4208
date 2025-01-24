#include "Player.h"
#include "Input.h"
#include "Window.h"
#include "DxLib.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "Water.h"
#include "Inversion.h"
#include "StageManager.h"
#include <random>
#include"imgui.h"

Player::~Player() {
	RemoveFontResourceEx(font, FR_PRIVATE, NULL);
}

void Player::Initialize() {

	soundPlayManager = SoundPlayManager::Instance();
	font = "Resources\\Texture\\Ronde-B_square.otf";
	AddFontResourceEx(font, FR_PRIVATE, NULL);
	ChangeFont("�����h B �X�N�G�A", DX_CHARSET_DEFAULT);
	SetFontSize(50);
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Player.png");

	size_ = baseSize;

	//�p�[�e�B�N��������
	bubbleEmitter = std::make_shared<BubbleEmitter>();
	splashEmitter = std::make_shared<SplashEmitter>();
	bubbleEmitter->Initialize(20);
	splashEmitter->Initialize(30);

	objectType_ = ObjectType::PLAYER;
	CollisionManager::GetInstance()->AddObject(this);
	StageManager::GetInstance()->SetIsClear(false);
}

void Player::Update() {

	horizontal = Water::GetInstance()->GetHorizontal();
	ObjectUpdate();
	color = GetColor(255, 255, 255);

	if (pos_.y + size_.y / 2 > WIN_HEIGHT || pos_.y - size_.y / 2 < 0 ||
		pos_.x + size_.x / 2 > WIN_WIDTH || pos_.x - size_.x / 2 < 0) {
		isGameover = true;
	}

	//���]���łȂ����
	if (!Inversion::GetInstance()->GetIsInversion()) {

		isDrawGuide = false;
		isExclude_ = true;
		isFront = false;

		if (isBurial && !Inversion::GetInstance()->GetEndInversion()) {
			isGameover = true;
		}

		if (!StageManager::GetInstance()->GetIsClear() && !isGameover) {

			if (frame <= 0) {
				//����\
				Operation();

				//�W�����v�ɂ���ċ󒆂ɂ���Ƃ��̏���
				//�v���C���[���W�ɏd�͂����Z
				pos_.y += gravity;	//gravity�̏����l�̓}�C�i�X�̂��ߍŏ��͏�����ɓ���

				//�������x�����X�ɏグ��(�������͔���)
				gravity += 1.0f / (isUnderWater + 1);
			}
		}
	}
	else {
		//���]���͓����蔻�薳��
		isExclude_ = false;
		isFront = true;
	}


	if (oldPos_.y + size_.y / 2 < horizontal && pos_.y + size_.y / 2 >= horizontal) {
		soundPlayManager->SoundPlay(soundPlayManager->GetSound().waterA, 100);
	}

	if (isFront) {

		if (frame <= frameMax) {
			frame++;
		}
	}
	else {
		if (frame >= 0) {
			frame--;
		}
	}

	inverSize = {
	Easing(frame / frameMax) * 20.0f,
	Easing(frame / frameMax) * 20.0f };

	//��������n��ɏオ��邩����
	if (gravity <= 0 && pos_.y <= horizontal && isUnderWater) {
		canCrawlUp = true;

		if (!Inversion::GetInstance()->GetIsInversion() && !StageManager::GetInstance()->GetIsClear()) {
			pos_.y = horizontal;
		}
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

	if (isGameover && guideTimer <= 0) {
		soundPlayManager->SoundPlay(soundPlayManager->GetSound().gameover, 150);
	}

	if ((isDrawGuide && guideTimer <= guideTimerMax) || isGameover) {
		guideTimer += guideTimerMax / 10;
	}
	else if (!isDrawGuide && guideTimer >= 0) {
		guideTimer -= guideTimerMax / 60;
	}

	//�p�[�e�B�N���X�V
	bubbleEmitter->SetHorizontal(horizontal);
	splashEmitter->SetHorizontal(horizontal);
	bubbleEmitter->Update(pos_);
	splashEmitter->Update(pos_, size_.y / 2, gravity);

	//�[�Ŏ~�܂�
	if (pos_.x >= WIN_WIDTH - size_.x / 2) {
		pos_.x = WIN_WIDTH - size_.x / 2;
	}

	if (pos_.x <= size_.x / 2) {
		pos_.x = size_.x / 2;
	}

	//��ʂŎ~�܂�(��)
	if (pos_.y >= WIN_HEIGHT - size_.y / 2) {
		pos_.y = WIN_HEIGHT - size_.y / 2;
		canJumpTimer = canJumpTimerMax;
		canJump = true;
		gravity = 0;
	}

	if (pos_.y < 0 + size_.y / 2) {
		pos_.y = size_.y / 2;
		gravity = 0;
	}

	isBurial = false;

#ifdef _DEBUG
	ImGui::Begin("Player");

	ImGui::Text("%f", gravity);

	ImGui::End();
#endif

}

//�L�[���͂ő���ł��鏈��
void Player::Operation() {

	Move();
	Jump();

	//�L�[����Ŕ��]
	if (!Water::GetInstance()->GetIsChangeHorizontal() && !StageManager::GetInstance()->GetIsClear()) {
		if (!Input::GetIsUsePad())
		{
			if (Input::GetKeyTrigger(Input::Key::Q)) {
				InversionProcess();

				soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA, 100);
			}
		}
		else
		{
			if (Input::TriggerPadKey(PAD_INPUT_3)) {
				InversionProcess();

				soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA, 100);
			}
		}
	}
}

void Player::InversionProcess()
{
	Inversion::GetInstance()->SetIsInversion();
}

//���ړ�
void Player::Move() {


	if (!Input::GetIsUsePad())
	{
		if (Input::GetKey(Input::Key::A)) {
			MoveProcessLeft();
		}

		if (Input::GetKey(Input::Key::D)) {
			MoveProcessRight();
		}

	}
	else
	{
		if (Input::PadX() < 0) {
			MoveProcessLeft();
		}
		if (Input::PadX() > 0) {
			MoveProcessRight();
		}
	}

}

void Player::MoveProcessRight()
{
	if (pos_.x + size_.x / 2 < WIN_WIDTH)
	{
		pos_.x += speed;
		direction = Direction::RIGHT;
	}
}

void Player::MoveProcessLeft()
{
	if (pos_.x - size_.x / 2 > 0)
	{
		pos_.x -= speed;
		direction = Direction::LEFT;
	}
}

//�W�����v
void Player::Jump() {
	if (!Input::GetIsUsePad())
	{
		if (Input::GetKeyTrigger(Input::Key::Space) && canJump) {

			JumpProcess();
		}

	}
	else
	{
		if (Input::TriggerPadKey(PAD_INPUT_1) && canJump) {

			JumpProcess();
		}
	}
}

void Player::JumpProcess()
{
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

	if (isUnderWater) {
		soundPlayManager->SoundPlay(soundPlayManager->GetSound().swim, 100);
	}
	else {
		soundPlayManager->SoundPlay(soundPlayManager->GetSound().jump, 100);
	}

}

void Player::Draw() {

	if (size_.x > 0) {

		//DrawBox(pos_.x - size_.x/2, pos_.y - size_.y/2, pos_.x + size_.x/2, pos_.y + size_.y/2, GetColor(255,255,255), true);
		if (direction == Direction::RIGHT) {
			DrawExtendGraph(
				(int)(pos_.x - size_.x / 2 - inverSize.x / 2), (int)(pos_.y - size_.y / 2 - inverSize.y / 2),
				(int)(pos_.x + size_.x / 2 + inverSize.x / 2), (int)(pos_.y + size_.y / 2 + inverSize.y / 2),
				textruehandle_, true);
		}
		else {
			DrawExtendGraph(
				(int)(pos_.x + size_.x / 2 + inverSize.x / 2), (int)(pos_.y - size_.y / 2 - inverSize.y / 2),
				(int)(pos_.x - size_.x / 2 - inverSize.x / 2), (int)(pos_.y + size_.y / 2 + inverSize.y / 2),
				textruehandle_, true);
		}
	}

	DrawCircle(pos_.x, pos_.y, Easing(frame / frameMax) * 64.0f, GetColor(255, 255, 255), false);

	bubbleEmitter->Draw();
	splashEmitter->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, guideTimer);

	if (isGameover) {
		DrawString(200, 200, "�u���b�N�ɂԂ���Ă��܂����c", GetColor(255, 100, 100));

		if (!Input::GetIsUsePad()) {
			DrawBox(670, 505, 720, 555, GetColor(255, 255, 255), false);
			DrawString(400, 500, "���Z�b�g �c R ", GetColor(255, 255, 255));
		}
		else {
			DrawCircle(695, 530, 27, GetColor(255, 255, 255), false);
			DrawString(400, 500, "���Z�b�g �c Y ", GetColor(255, 255, 255));
		}
	}
	else {
		DrawString(200, 200, "�u���b�N���ז��łЂ�����Ԃ��Ȃ��c", GetColor(255, 100, 100));
	}


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Player::OnCollision(Object* objct) {

	//�u���b�N��ɏ���Ă���Ƃ��̏���
	if (static_cast<uint32_t>(pos_.y + size_.y / 2) <= static_cast<uint32_t>(objct->GetPos().y - objct->GetSize().y / 2)&&objct->IsExclude()) {
		canJumpTimer = canJumpTimerMax;
		gravity = 0.0f;
	}

	//���ł��̏���
	if ((pos_.y - size_.y / 2) >= (objct->GetPos().y + objct->GetSize().y / 2)) {
		gravity = 0.0f;
	}

	if (Inversion::GetInstance()->GetEndInversion()) {
		//�u���b�N�ɖ��܂��Ă����玩���ōĂє��]
		if (BurialJudge(objct)) {
			isDrawGuide = true;
			Inversion::GetInstance()->SetIsInversion();
		}
	}

	if (objct->GetObjectType() == ObjectType::DRAIN) {
		if (!Input::GetIsUsePad())
		{
			if (Input::GetKeyTrigger(Input::Key::W) && !Water::GetInstance()->GetIsChangeHorizontal()) {
				Water::GetInstance()->SetTentHorizontal(objct->GetPos().y);
				soundPlayManager->SoundPlay(soundPlayManager->GetSound().waterB, 100);
			}
		}
		else
		{
			//�p�b�g�ł�B�{�^��
			if (Input::TriggerPadKey(PAD_INPUT_2) && !Water::GetInstance()->GetIsChangeHorizontal()) {
				Water::GetInstance()->SetTentHorizontal(objct->GetPos().y);
				soundPlayManager->SoundPlay(soundPlayManager->GetSound().waterB, 100);
			}
		}
	}

	if (objct->GetObjectType() == ObjectType::GOAL && StageManager::GetInstance()->GetIsClear()) {

		if (size_.x == baseSize.x) {
			soundPlayManager->SoundPlay(soundPlayManager->GetSound().clear, 255 * 0.75f);

		}

		if (size_.x > 0) {
			size_.x -= baseSize.x / 60;
		}
		else {
			size_.x = 0;
		}
		if (size_.y > 0) {
			size_.y -= baseSize.y / 60;
		}
		else {
			size_.y = 0;
		}

		pos_.x += (objct->GetPos().x - pos_.x) / 4;
		pos_.y += (objct->GetPos().y - pos_.y) / 4;
	}

	if (BurialJudge(objct)) {
		isBurial = true;
	}
}

bool Player::BurialJudge(Object* objct) {
	//�u���b�N�̃I�u�W�F�N�g�^�C�v����
	if (objct->IsExclude()) {

		//�u���b�N�ɖ��܂��Ă��邩����
		if (pos_.x + size_.x / 2 - 1 >= objct->GetPos().x - objct->GetSize().x / 2 &&
			pos_.x - size_.x / 2 + 1 <= objct->GetPos().x + objct->GetSize().x / 2 &&
			pos_.y + size_.y / 2 - 1 >= objct->GetPos().y - objct->GetSize().y / 2 &&
			pos_.y - size_.y / 2 + 1 <= objct->GetPos().y + objct->GetSize().y / 2) {

			return true;
		}
	}

	return false;
}