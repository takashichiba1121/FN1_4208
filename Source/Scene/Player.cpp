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

	//水中から地上に上がれるか判定
	if (gravity <= 0 && pos_.y <= horizontal && isUnderWater) {
		canCrawlUp = true;
		pos_.y = horizontal;
	}
	else {
		canCrawlUp = false;
	}

	//水面の上か下かを判定(仮)
	if (pos_.y >= horizontal) {
		isUnderWater = true;
	}
	else {
		isUnderWater = false;
	}

	//地上と水中でスピードを変える
	if (isUnderWater) {
		speed = WaterSpeed;
	}
	else {
		speed = GroundSpeed;
	}

	//ジャンプによって空中にいるときの処理
	//プレイヤー座標に重力を加算
	pos_.y += gravity;	//gravityの初期値はマイナスのため最初は上方向に動く

	//落下速度を徐々に上げる(水中時は半減)
	gravity += 1.0f / (isUnderWater + 1);

	//落下速度の上限を決める(水中時は半減)
	if (gravity >= MaxGravity / (isUnderWater + 1)) {
		gravity = MaxGravity / (isUnderWater + 1);
	}

	//水中であれば無限ジャンプ可能
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

	//パーティクル更新
	bubbleEmitter->Update(pos_);
	bubbleEmitter->SetHorizontal(horizontal);

	//底面で止まる(仮)
	if (pos_.y >= underLine - size_.y / 2) {
		pos_.y = underLine - size_.y / 2;
		canJumpTimer = canJumpTimerMax;
		canJump = true;
	}

}

//キー入力で操作できる処理
void Player::Operation() {

	Move();
	Jump();

	//↑↓キーで水平線調節
	if (Input::GetKey(Input::Key::Up) && horizontal > 0) {
		horizontal -= 2.0f;
	}
	if (Input::GetKey(Input::Key::Down) && horizontal < 720) {
		horizontal += 2.0f;
	}

	//←→キーで底面調節
	if (Input::GetKey(Input::Key::Left) && underLine > 0) {
		underLine -= 2.0f;
	}
	if (Input::GetKey(Input::Key::Right) && underLine < 720) {
		underLine += 2.0f;
	}

	//プレイヤーの位置リセット
	if (Input::GetKeyTrigger(Input::Key::R)) {
		pos_ = { 100,100 };
	}
}

//横移動
void Player::Move() {
	if (Input::GetKey(Input::Key::A) && pos_.x - size_.x / 2 > 0) {
		pos_.x -= speed;
	}
	if (Input::GetKey(Input::Key::D) && pos_.x + size_.x / 2 < 1280) {
		pos_.x += speed;
	}
}

//ジャンプ
void Player::Jump() {
	if (Input::GetKeyTrigger(Input::Key::Space) && canJump) {

		//水中から地上に上がるときは地上と同じようなジャンプ(少し低め)
		if (canCrawlUp) {
			isUnderWater = false;
			initJumpVelocity = -MaxGravity / 1.25f;
		}
		else {
			initJumpVelocity = -MaxGravity;
		}

		//ジャンプの初速(水中時は半減)
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
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "horizontal : %f (↑↓キーで調整)", horizontal);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "underLine : %f (←→キーで調整)", underLine);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "canJump : %d", canJump);
}

void Player::OnCollision(Object* objct) {
	if ((pos_.y + size_.y / 2) <= (objct->GetPos().y - objct->GetSize().y / 2)) {
		canJumpTimer = canJumpTimerMax;
		gravity = 0.0f;
	}
}