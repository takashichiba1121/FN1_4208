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
	ChangeFont("ロンド B スクエア", DX_CHARSET_DEFAULT);
	SetFontSize(50);
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Player.png");

	size_ = baseSize;

	//パーティクル初期化
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

	//反転中でなければ
	if (!Inversion::GetInstance()->GetIsInversion()) {

		isDrawGuide = false;
		isExclude_ = true;
		isFront = false;

		if (isBurial && !Inversion::GetInstance()->GetEndInversion()) {
			isGameover = true;
		}

		if (!StageManager::GetInstance()->GetIsClear() && !isGameover) {

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
	}
	else {
		//反転中は当たり判定無視
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

	//水中から地上に上がれるか判定
	if (gravity <= 0 && pos_.y <= horizontal && isUnderWater) {
		canCrawlUp = true;

		if (!Inversion::GetInstance()->GetIsInversion() && !StageManager::GetInstance()->GetIsClear()) {
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

	if (isGameover && guideTimer <= 0) {
		soundPlayManager->SoundPlay(soundPlayManager->GetSound().gameover, 150);
	}

	if ((isDrawGuide && guideTimer <= guideTimerMax) || isGameover) {
		guideTimer += guideTimerMax / 10;
	}
	else if (!isDrawGuide && guideTimer >= 0) {
		guideTimer -= guideTimerMax / 60;
	}

	//パーティクル更新
	bubbleEmitter->SetHorizontal(horizontal);
	splashEmitter->SetHorizontal(horizontal);
	bubbleEmitter->Update(pos_);
	splashEmitter->Update(pos_, size_.y / 2, gravity);

	//端で止まる
	if (pos_.x >= WIN_WIDTH - size_.x / 2) {
		pos_.x = WIN_WIDTH - size_.x / 2;
	}

	if (pos_.x <= size_.x / 2) {
		pos_.x = size_.x / 2;
	}

	//底面で止まる(仮)
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

//キー入力で操作できる処理
void Player::Operation() {

	Move();
	Jump();

	//キー操作で反転
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

//横移動
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

//ジャンプ
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
		DrawString(200, 200, "ブロックにつぶされてしまった…", GetColor(255, 100, 100));

		if (!Input::GetIsUsePad()) {
			DrawBox(670, 505, 720, 555, GetColor(255, 255, 255), false);
			DrawString(400, 500, "リセット … R ", GetColor(255, 255, 255));
		}
		else {
			DrawCircle(695, 530, 27, GetColor(255, 255, 255), false);
			DrawString(400, 500, "リセット … Y ", GetColor(255, 255, 255));
		}
	}
	else {
		DrawString(200, 200, "ブロックが邪魔でひっくり返せない…", GetColor(255, 100, 100));
	}


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Player::OnCollision(Object* objct) {

	//ブロック上に乗っているときの処理
	if (static_cast<uint32_t>(pos_.y + size_.y / 2) <= static_cast<uint32_t>(objct->GetPos().y - objct->GetSize().y / 2)&&objct->IsExclude()) {
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
			//パットではBボタン
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
	//ブロックのオブジェクトタイプ判定
	if (objct->IsExclude()) {

		//ブロックに埋まっているか判定
		if (pos_.x + size_.x / 2 - 1 >= objct->GetPos().x - objct->GetSize().x / 2 &&
			pos_.x - size_.x / 2 + 1 <= objct->GetPos().x + objct->GetSize().x / 2 &&
			pos_.y + size_.y / 2 - 1 >= objct->GetPos().y - objct->GetSize().y / 2 &&
			pos_.y - size_.y / 2 + 1 <= objct->GetPos().y + objct->GetSize().y / 2) {

			return true;
		}
	}

	return false;
}