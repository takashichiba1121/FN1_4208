#include "GameScene.h"
#include "DxLib.h"
#include"Input.h"
#include"Window.h"
#include"CollisionManager.h"
#include"Inversion.h"
#include "TextureManager.h"

void GameScene::Initialize()
{
	pause_ = std::make_unique<Pause>();

	soundPlayManager = SoundPlayManager::Instance();

	if (!CheckSoundMem(soundPlayManager->GetBGM().gameScene)) {
		soundPlayManager->BGMStop(soundPlayManager->GetBGM().titleScene);
		soundPlayManager->BGMPlay(soundPlayManager->GetBGM().gameScene);
	}

	pause_->Initialize();
	Inversion::GetInstance()->Initialize();

	backGroundTextruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\background.png");

#ifdef _DEBUG
	test.Initialize();
#endif
}

void GameScene::Update()
{
	if (isPause==false)
	{

#ifdef _DEBUG
	test.Update();
#endif
	pause_->InGameUpdate();

		Inversion::GetInstance()->Update();

		Water::GetInstance()->Update();

		StageManager::GetInstance()->Update();

		CollisionManager::GetInstance()->Update();

		//パットはYボタン
		if ((Input::GetKeyTrigger(Input::Key::R)|| Input::TriggerPadKey(PAD_INPUT_4)) && !Inversion::GetInstance()->GetIsInversion())
		{
			Inversion::GetInstance()->Initialize();
			StageManager::GetInstance()->NowStageReset();
			soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionB);
		}

		//パットはStartだかoptionボタン
		if (Input::GetKeyTrigger(Input::Key::T)|| Input::TriggerPadKey(PAD_INPUT_8))
		{
			isPause = true;
			pause_->StartGetPause();

			soundPlayManager->SoundPlay(soundPlayManager->GetSound().waterA);
		}

	}
	else
	{
		pause_->Update();

		if (pause_->IsEndGetPause())
		{
			isPause = false;
		}
	}
}

void GameScene::Draw()
{
	//背景描画
	if (Inversion::GetInstance()->GetIsFront()) {

		DrawExtendGraphF(
			0, Easing(Inversion::GetInstance()->GetFrame() / 60) * 720,
			1280, 720 - Easing(Inversion::GetInstance()->GetFrame() / 60) * 720,
			backGroundTextruehandle_, true);
	}
	else {
		DrawExtendGraphF(
			0, 720 - Easing(Inversion::GetInstance()->GetFrame() / 60) * 720,
			1280, Easing(Inversion::GetInstance()->GetFrame() / 60) * 720,
			backGroundTextruehandle_, true);
	}
	
	//水、オブジェクト描画
	if (!Inversion::GetInstance()->GetIsReverse()) {
		Water::GetInstance()->DrawUp();
		StageManager::GetInstance()->Draw();
		Water::GetInstance()->DrawUnder();
	}
	else {
		Water::GetInstance()->DrawUnder();
		StageManager::GetInstance()->Draw();
		Water::GetInstance()->DrawUp();
	}

#ifdef _DEBUG
	test.Draw();
#endif

	if (isPause)
	{
		pause_->Draw();
	}
	else
	{
		pause_->InGameDraw();
	}
}

void GameScene::Finalize()
{
	//CollisionManager::GetInstance()->AllDelete();
}
