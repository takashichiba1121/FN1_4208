#include "Player.h"
#include "Input.h"
#include "Window.h"
#include "DxLib.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "Water.h"
#include "Inversion.h"
#include <random>
#include"imgui.h"

Player::~Player() {
	RemoveFontResourceEx(font, FR_PRIVATE, NULL);
}

void Player::Initialize() {

	font = "Resources\\Texture\\Ronde-B_square.otf";
	AddFontResourceEx(font, FR_PRIVATE, NULL);
	ChangeFont("ロンド B スクエア", DX_CHARSET_DEFAULT);
	SetFontSize(50);
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Player.png");

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
	color = GetColor(255, 255, 255);

	//反転中でなければ
	if (!Inversion::GetInstance()->GetIsInversion()) {

		isDrawGuide = false;
		isExclude_ = true;
		isFront = false;

		if (frame <= 0) {
			//操作可能
			Operation();

			//ジャンプによって空中にいるときの処理
			//プレイヤー座標に重力を加算
			pos_.y += gravity;	//gravityの初期値はマイナスのため最初は上方向に動く

			//落下速度を徐々に上げる(水中時は半減)
			gravity += 1.0f / (isUnderWater + 1);
		}
	}
	else {
		//反転中は当たり判定無視
		isExclude_ = false;
		isFront = true;
	
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

	if (isDrawGuide && guideTimer <= guideTimerMax) {
		guideTimer += guideTimerMax / 10;
	}
	else if(!isDrawGuide && guideTimer >= 0){
		guideTimer -= guideTimerMax / 60;
	}

	if (guideTimer > guideTimerMax){
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

#ifdef _DEBUG
	ImGui::Begin("Player");

	ImGui::Text("%f",gravity);

	ImGui::End();
#endif

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
		direction = Direction::LEFT;
	}
	if (Input::GetKey(Input::Key::D) && pos_.x + size_.x / 2 < 1280) {
		pos_.x += speed;
		direction = Direction::RIGHT;
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

	if (direction == Direction::RIGHT) {
		DrawExtendGraph(
			(int)(pos_.x - size_.x / 2 - inverSize.x / 2), (int)(pos_.y - size_.y / 2 - inverSize.y / 2),
			(int)(pos_.x + size_.x / 2 + inverSize.x / 2), (int)(pos_.y + size_.y / 2 + inverSize.y / 2),
			textruehandle_, true);
	}
	else {
		DrawExtendGraph(
			(int)(pos_.x + size_.x / 2 + inverSize.x / 2), (int)(pos_.y - size_.y / 2 - inverSize.y / 2),
			(int)(pos_.x - size_.x / 2- inverSize.x / 2), (int)(pos_.y + size_.y / 2 + inverSize.y / 2),
			textruehandle_, true);
	}
	
	DrawCircle(pos_.x, pos_.y, Easing(frame / frameMax) * 64.0f, GetColor(255, 255, 255), false);

	bubbleEmitter->Draw();
	splashEmitter->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, guideTimer);
	DrawString(200, 200, "ブロックが邪魔でひっくり返せない…", GetColor(255, 100, 100));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
}

void Player::OnCollision(Object* objct) {

	//ブロック上に乗っているときの処理
	if (static_cast<uint32_t>(pos_.y + size_.y / 2) <= static_cast<uint32_t>(objct->GetPos().y - objct->GetSize().y / 2)) {
		canJumpTimer = canJumpTimerMax;
		gravity = 0.0f;
	}
	else if (gravity >= 3)
	{
		gravity = gravity;
	}

	//頭打ちの処理
	if ((pos_.y - size_.y / 2) >= (objct->GetPos().y + objct->GetSize().y / 2)) {
		gravity = 0.0f;
	}

	if (Inversion::GetInstance()->GetEndInversion()) {
		//ブロックに埋まっていたら自動で再び反転
		if (BurialJudge(objct)) {
			isDrawGuide = true;
			Inversion::GetInstance()->SetIsInversion();
		}
	}

	if (objct->GetObjectType() == ObjectType::DRAIN) {
		if (Input::GetKeyTrigger(Input::Key::W) && !Water::GetInstance()->GetIsChangeHorizontal()) {
			Water::GetInstance()->SetTentHorizontal(objct->GetPos().y);
		}
	}
	
}

bool Player::BurialJudge(Object* objct){
	//ブロックのオブジェクトタイプ判定
	if (objct->IsExclude()) {

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