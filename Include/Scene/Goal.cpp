#include "Goal.h"
#include "Input.h"
#include "CollisionManager.h"
#include <random>
#include "TextureManager.h"
#include"StageManager.h"
#include "SceneManager.h"
#include "SoundPlayManager.h"
#include"Inversion.h"

void Goal::Initialize()
{
	
	objectType_ = ObjectType::GOAL;
	isExclude_ = false;
	CollisionManager::GetInstance()->AddObject(this);

	//パーティクル初期化
	//パーティクル初期化
	//confettiEmitter = std::make_unique<ConfettiEmiitter>();
	//confettiEmitter->Initialize(5);

	//画像読み込み
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\CloseDoor_1.png");
	textruehandle2_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\OpenDoor_1.png");
	textruehandle3_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\DoorKey_1.png");
	textruehandle4_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\clearText.png");
	textruehandle5_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\next.png");
	textruehandle6_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\back.png");
	textruehandle7_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\clear.png");

	//ゴールロックの初期状態
	isLock = false;
	isClear = false;
}

void Goal::Update()
{
	horizontal = Water::GetInstance()->GetHorizontal();
	ObjectUpdate();

	//開閉チェック
	if (Input::GetKeyTrigger(/*Input::Key::Up*/Input::Key::L) && isLock == false) {
		//keydata->isLock=true;
		isLock = true;
	}
	else if (Input::GetKeyTrigger(/*Input::Key::Down*/Input::Key::L) && isLock == true) {
		isLock = false;
	}

	//鍵が一つ以上あるなら扉をしめる
	if (StageManager::GetInstance()->GetKeyNum() <= 0) {
		isLock = false;
	}else {
		isLock = true;
	}

	//水平線より下か(上か)
	if (pos_.y + size_.y / 2 >= horizontal) {
		isUnderWater = true;
	}
	else {
		isUnderWater = false;
	}


	if (isUnderWater) {
		//ゴール(閉)
		isCollision_ = true;
	}
	else {
		//ゴール(開)
		isCollision_ = true;
	}

	//演出(開閉時)


	//演出(衝突時)
	/*if (isClear == true) {
	if (a <= 4) {
	timer--;

	if (timer <= 0) {
	timer = coolTime;
	a += 0.1f;
	}
	}
	}*/

	//演出(遷移)
	if (isClear) {
		NextSelect();
		/*confettiEmitter->Update();
		NextSelect();
		if (easingFrame_ < maxEasingFrame_) {
			easingFrame_++;
			f = ExpansionGoalText(static_cast<float>(easingFrame_) / static_cast<float>(maxEasingFrame_));
		}*/

		/*if (isUnderWater) {
			isClear = false;
		}*/
	}
}

void Goal::Inversion(const float easing) {
	pos_.y = easeSPos_ + easing * (easeEPos_ - easeSPos_);
	size_.y = tentSize_ * abs(easing - 0.5f) * 2;
}

void Goal::NextSelect()
{
	if (Input::GetKeyTrigger(Input::Key::Right)||(Input::OldPadX()<=500&& Input::PadX() > 500)) {
			nextStageSelect_ = 1;
	}
	else if (Input::GetKeyTrigger(Input::Key::Left) || (Input::OldPadX() >= -500 && Input::PadX() < -500)) {
			nextStageSelect_ = -1;
	}

	if (Input::GetKeyTrigger(Input::Key::Space))
	{
		if (nextStageSelect_==1) {
			//次のステージへ
			//StageManager::GetInstance()->NextLevelLoad();
			StageManager::GetInstance()->NextSelect(false);
			isClear = false;
			isLock = true;
			SoundPlayManager::Instance()->SoundPlay(SoundPlayManager::Instance()->GetSound().select, 255 * 0.5f);
		}
		else if (nextStageSelect_ == -1) {
			//セレクト画面へ
			//SceneManager::GetInstance()->ChangeScene("STAGESELECT");
			StageManager::GetInstance()->NextSelect(true);
			SoundPlayManager::Instance()->SoundPlay(SoundPlayManager::Instance()->GetSound().select, 255 * 0.5f);
		}
	}
	StageManager::GetInstance()->SetNextStageSelect(nextStageSelect_);
}

float Goal::ExpansionGoalText(float x)
{
	return 1 - cos((x * 3.141592) / 2);
}

void Goal::Draw()
{
	if (isUnderWater == false && isLock == true || isUnderWater == true && isLock==true) {
		//ゴール(鍵あり閉)
		DrawRotaGraph3F(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f,
			(double)(size_.x / 64.0), (double)(size_.y / 64.0), 0, textruehandle_, true);
		DrawRotaGraph3F(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f,
			(double)(size_.x / 64.0), (double)(size_.y / 64.0), 0, textruehandle3_, true);
		//DrawGraph(pos_.x - size_.x / 2, pos_.y - size_.y / 2, textruehandle_, true);
		//DrawGraph(pos_.x - size_.x / 2, pos_.y - size_.y / 2, textruehandle3_, true);
		//DrawFormatString(pos_.x - 15, pos_.y - 10, GetColor(0, 0, 0), "Goal");
	}
	else if (isUnderWater) {
		//ゴール(閉)
		DrawRotaGraph3F(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f,
			(double)(size_.x / 64.0), (double)(size_.y / 64.0), 0, textruehandle_, true);
		//DrawGraph(pos_.x - size_.x / 2, pos_.y - size_.y / 2, textruehandle_, true);
	}
	else {
		//ゴール(開)
		DrawRotaGraph3F(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f,
			(double)(size_.x / 64.0), (double)(size_.y / 64.0), 0, textruehandle2_, true);
		//DrawGraph(pos_.x - size_.x / 2, pos_.y - size_.y / 2, textruehandle2_, true);
	}

	//if (isClear) {
	//	//クリア
	//	//DrawBox(1280 / a, 720 / a, 1280 - 1280 / a, 720 - 720 / a, GetColor(255, 255, 255), true);
	//	//DrawFormatString(0, 100, GetColor(0, 255, 0), "clear!!");
	//	confettiEmitter->Draw();
	//	//ゴールの文字
	//	DrawGraph(1280/2-640/2, 720/ 2-100/2, textruehandle4_, true);
	//	DrawRotaGraph3(1280 / 2, 720 / 2 , 640 / 2 , 100 / 2, f, f, 0, textruehandle4_, TRUE);//前の
	//	

	//	
	//	//次への案内
	//	if (720 - (256 - 64) * f <= horizontal) {
	//		DrawRotaGraph3(1280 / 2, 720 - (256 - 64) * f, 256 / 2, 256 / 2, f * 1.5, f * 1.5, 0, textruehandle7_, TRUE);
	//	}
	//	else if ((256 - 74) * f >= horizontal) {
	//		DrawRotaGraph3(1280 / 2, 0 + (256 - 74) * f, 256 / 2, 256 / 2, f * 1.5, f * 1.5, 0, textruehandle7_, TRUE);
	//	}
	//	else {
	//		DrawRotaGraph3(1280 / 2, horizontal, 256 / 2, 256 / 2, f * 1.5, f * 1.5, 0, textruehandle7_, TRUE);
	//	}

	//	if (720-256/4 <= horizontal) {
	//		DrawRotaGraph3(1280 - 1280 / 4, 720 - 256 / 4, 256 / 2, 256 / 2, 0.5, 0.5, 0, textruehandle5_, TRUE);
	//		DrawRotaGraph3(1280 / 4, 720 - 256 / 4, 256 / 2, 256 / 2, 0.5, 0.5, 0, textruehandle6_, TRUE);
	//	}
	//	else if (256 / 4 >= horizontal) {
	//		DrawRotaGraph3(1280 - 1280 / 4, 0 + 256 / 4, 256 / 2, 256 / 2, 0.5, 0.5, 0, textruehandle5_, TRUE);
	//		DrawRotaGraph3(1280 / 4, 0 + 256 / 4, 256 / 2, 256 / 2, 0.5, 0.5, 0, textruehandle6_, TRUE);
	//	}
	//	else {
	//		DrawRotaGraph3(1280 - 1280 / 4, horizontal, 256 / 2, 256 / 2, 0.5, 0.5, 0, textruehandle5_, TRUE);
	//		DrawRotaGraph3(1280 / 4, horizontal, 256 / 2, 256 / 2, 0.5, 0.5, 0, textruehandle6_, TRUE);
	//	}
	//	
	//}
}

void Goal::OnCollision(Object* objct)
{
	if (objct->GetObjectType() == ObjectType::PLAYER && isUnderWater == false && isLock == false&&
		Inversion::GetInstance()->GetIsInversion()==false&& !Inversion::GetInstance()->GetEndInversion()) {
		//DrawFormatString(0, 100, GetColor(0, 255, 0), "clear!!");
		isClear = true;
		StageManager::GetInstance()->SetIsClear(true);
	}
}