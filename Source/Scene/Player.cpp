#include "Player.h"
#include "Input.h"
#include "Window.h"
#include "DxLib.h"
#include "CollisionManager.h"
#include "Water.h"
#include "Inversion.h"
#include <random>
#include"imgui.h"

void Player::Initialize() {

	pos_ = { 100,100 };
	size_ = { 64,64 };

	//パーティクル初期化
	bubbleEmitter = std::make_unique<BubbleEmitter>();
	splashEmitter = std::make_unique<SplashEmitter>();
	bubbleEmitter->Initialize(20);
	splashEmitter->Initialize(30);

	objectType_ = ObjectType::PLAYER;
	CollisionManager::GetInstance()->AddObject(this);
}

void Player::Update() {

	horizontal = Water::GetInstance()->GetHorizontal();
	ObjectUpdate();
	color = GetColor(255, 0, 0);

	//反転中でなければ
	if (!Inversion::GetInstance()->GetIsInversion()) {

		isExclude_ = true;

		//操作可能
		Operation();

		//ジャンプによって空中にいるときの処理
		//プレイヤー座標に重力を加算
		pos_.y += gravity;	//gravityの初期値はマイナスのため最初は上方向に動く

		//落下速度を徐々に上げる(水中時は半減)
		gravity += 1.0f / (isUnderWater + 1);
	}
	else {
		//反転中は当たり判定無視
		isExclude_ = false;
	}

	//水中から地上に上がれるか判定
	if (gravity <= 0 && pos_.y <= horizontal && isUnderWater) {
		canCrawlUp = true;

		if (!Inversion::GetInstance()->GetIsInversion()) {
			pos_.y = horizontal;
		}
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
	bubbleEmitter->SetHorizontal(horizontal);
	splashEmitter->SetHorizontal(horizontal);
	bubbleEmitter->Update(pos_);
	splashEmitter->Update(pos_,size_.y / 2, gravity);

	//底面で止まる(仮)
	if (pos_.y >= WIN_HEIGHT - size_.y / 2) {
		pos_.y = WIN_HEIGHT - size_.y / 2;
		canJumpTimer = canJumpTimerMax;
		canJump = true;
		gravity = 0;
	}

	ImGui::Begin("Player");

	ImGui::Text("%f",gravity);

	ImGui::End();

}

//キー入力で操作できる処理
void Player::Operation() {

	Move();
	Jump();

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

	bubbleEmitter->Draw();
	splashEmitter->Draw();
}

void Player::OnCollision(Object* objct) {
	//ブロック上に乗っているときの処理
	if ((pos_.y + size_.y / 2) <= (objct->GetPos().y - objct->GetSize().y / 2)) {
		canJumpTimer = canJumpTimerMax;
		gravity = 0.0f;
	}

	//頭打ちの処理
	if ((pos_.y - size_.y / 2) >= (objct->GetPos().y + objct->GetSize().y / 2)) {
		gravity = 0.0f;
	}

	if (Inversion::GetInstance()->GetEndInversion()) {
		//ブロックに埋まっていたら自動で再び反転
		if (BurialJudge(objct)) {
			Inversion::GetInstance()->SetIsInversion();
		}
	}

	if (objct->GetObjectType() == ObjectType::DRAIN) {
		if (Input::GetKeyTrigger(Input::Key::W)) {
			Water::GetInstance()->SetTentHorizontal(objct->GetPos().y);
		}
	}
}

bool Player::BurialJudge(Object* objct){
	//ブロックのオブジェクトタイプ判定
	if (objct->GetObjectType() == ObjectType::FLOAT_BLOCK ||
		objct->GetObjectType() == ObjectType::NOT_FLOAT_BLOCK ||
		objct->GetObjectType() == ObjectType::BREAK_BLOCK) {

		//ブロックに埋まっているか判定
		if (pos_.x + size_.x / 2 - 1 >= objct->GetPos().x - objct->GetSize().x / 2 &&
			pos_.x - size_.x / 2 + 1 <= objct->GetPos().x + objct->GetSize().x / 2 &&
			pos_.y + size_.y / 2 - 1 >= objct->GetPos().y - objct->GetSize().y / 2 &&
			pos_.y - size_.y / 2 + 1 <= objct->GetPos().y + objct->GetSize().y / 2){

			return true;
		}
	}

	return false;
}