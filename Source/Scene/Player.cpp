#include "Player.h"
#include "Input.h"
#include "DxLib.h"

void Player::Initialize() {
	pos_ = { 100,100 };
}

void Player::Update() {

	Operation();

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
		speed = waterSpeed;
	}
	else {
		speed = groundSpeed;
	}

	//ジャンプによって空中にいるときの処理
	if (!isOnFloor) {

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
			canJump = false;
		}
	}
	else {
		canJump = true;
	}

	//ウィンドウの一番下で止まる
	if (pos_.y >= 720 - size_.y / 2) {
		pos_.y = 720 - size_.y / 2;
		isOnFloor = true;
	}

	
}

//キー入力で操作できる処理
void Player::Operation() {

	Move();
	Jump();

	//↑↓キーで水平線調節	
	if (Input::GetKey(Input::Key::Up)) {
		horizontal -= 2.0f;
	}
	if (Input::GetKey(Input::Key::Down)) {
		horizontal += 2.0f;
	}

}

//横移動
void Player::Move() {
	if (Input::GetKey(Input::Key::A)) {
		pos_.x -= speed;
	}
	if (Input::GetKey(Input::Key::D)) {
		pos_.x += speed;
	}
}

//ジャンプ
void Player::Jump() {
	if (Input::GetKeyTrigger(Input::Key::Space) && canJump) {
		isOnFloor = false;

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
		(int)(pos_.x - size_.x / 2), (int)(pos_.y - size_.x / 2),
		(int)(pos_.x + size_.x / 2), (int)(pos_.y + size_.x / 2),
		GetColor(250, 250, 250), true);

	DrawLine(0, (int)horizontal, 1280, (int)horizontal, GetColor(255, 255, 255));
	DrawFormatString(0, 0, GetColor(255, 255, 255), "horizontal : %f (↑↓キーで調整)", horizontal);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "isUnderWater : %d", isUnderWater);
}

void Player::OnCollision(Object* objct) {

}