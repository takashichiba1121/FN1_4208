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
		pos.y += gravity;	//gravityの初期値はマイナスのため最初は上方向に動く

		//落下速度を徐々に上げる(水中時は半減)
		gravity += 1.0f / (isUnderWater + 1);

		//落下速度の上限を決める(水中時は半減)
		if (gravity >= MaxGravity / (isUnderWater + 1)) {
			gravity = MaxGravity / (isUnderWater + 1);
		}

		//水中であれば無限ジャンプ可能
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

	//ウィンドウの一番下で止まる
	if (pos.y >= 720 - size.y / 2) {
		pos.y = 720 - size.y / 2;
		isOnFloor = true;
	}
	
}

//キー入力で操作できる処理
void Player::Operation() {

	Move();
	Jump();

	//↑↓キーで水平線調節
	
	if (Input::GetKey(Input::KEY::Up)) {
		horizontal -= 2.0f;
	}
	if (Input::GetKey(Input::KEY::Down)) {
		horizontal += 2.0f;
	}

}

//横移動
void Player::Move() {
	if (Input::GetKey(Input::KEY::A)) {
		pos.x -= speed;
	}
	if (Input::GetKey(Input::KEY::D)) {
		pos.x += speed;
	}
}

//ジャンプ
void Player::Jump() {
	if (Input::GetKeyTrigger(Input::KEY::Space) && isCanJump) {
		isOnFloor = false;

		//ジャンプの初速(水中時は半減)
		gravity = InitJumpVelocity / (isUnderWater + 1);
	}
}

void Player::Draw() {

	DrawBox(
		(int)(pos.x - size.x / 2), (int)(pos.y - size.x / 2),
		(int)(pos.x + size.x / 2), (int)(pos.y + size.x / 2),
		GetColor(250, 250, 250), true);

	DrawLine(0, horizontal, 1280, horizontal, GetColor(255, 255, 255));
	DrawFormatString(0, 0, GetColor(255, 255, 255), "horizontal : %f (↑↓キーで調整)", horizontal);
}