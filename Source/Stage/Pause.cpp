#include "Pause.h"
#include"TextureManager.h"
#include "DxLib.h"
#include"Input.h"
#include"SceneManager.h"
#include"StageManager.h"
#include<string>

void Pause::Initialize()
{
	soundPlayManager = SoundPlayManager::Instance();
	texturehandleTitle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\PauseTitle.png");
	texturehandleGame_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\PauseGame.png");
	texturehandleTutorial_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\PauseTutorial.png");
	texturehandleSelect_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\PauseSelect.png");
	inGameTexturehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\InGameTutorial.png");

	fontHandle_ = CreateFontToHandle("ロンド B スクエア", fontSize_, -1);
}

void Pause::InGameUpdate()
{
	if (CheckHitKeyAll(DX_CHECKINPUT_KEY) || CheckHitKeyAll(DX_CHECKINPUT_MOUSE)|| CheckHitKeyAll(DX_CHECKINPUT_PAD))
	{
		notPlay_ = true;
		inGameUIFrame_ = 0;
	}
	else
	{
		notPlay_ = false;
	}


	if (!notPlay_)
	{
		if (inGameUIFrame_ < inGameUIMaxFrame_)
		{
			inGameUIFrame_++;
		}
	}
	float f = static_cast<float>(inGameUIFrame_) / static_cast<float>(inGameUIMaxFrame_);

	ingamePos_.x = (0 - -192) * f;
	ingamePos_.y = (0 - -1068) * f;
	ingamePos_ -= {192, 1068};
}

void Pause::Update()
{
	float f = 0;

	switch (phase_)
	{
	case Phase::Before:
		pauseFrame_++;
		f = (float)pauseFrame_ / 10;
		size_ = { 1280 * f,720 * f };
		if (pauseFrame_ >= 10)
		{
			phase_ = Phase::Middle;
		}
		break;
	case Phase::Middle:
		if (isAlphaPlas_)
		{
			alpha_ += 5;
			if (alpha_>=255)
			{
				isAlphaPlas_ = false;
			}
		}
		else
		{
			alpha_-=5;
			if (alpha_ <= 0)
			{
				isAlphaPlas_ = true;
			}
		}


		if (!tutorial_)
		{
			if (Input::GetKeyTrigger(Input::Key::Up) || (Input::OldPadY() <= 500 && Input::PadY() > 500)) {
				select_--;
			}
			else if (Input::GetKeyTrigger(Input::Key::Down) || (Input::OldPadY() >= -500 && Input::PadY() < -500)) {
				select_++;
			}
			if (select_ < 0)
			{
				select_ = 0;
			}
			if (select_ > 3)
			{
				select_ = 3;
			}

			//パットはStartだかoptionボタン
			if (Input::GetKeyTrigger(Input::Key::Space) || Input::TriggerPadKey(PAD_INPUT_1))
			{
				if (select_ == 0)
				{
					phase_ = Phase::After;
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().waterA, 100);
				}
				else if (select_ == 1)
				{
					tutorial_ = true;
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA, 100);
				}
				else if (select_ == 2)
				{
					SceneManager::GetInstance()->ChangeScene("STAGESELECT");
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA, 100);
				}
				else if (select_ == 3)
				{
					SceneManager::GetInstance()->ChangeScene("TITLE");
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA, 100);
				}
			}
		}
		else
		{
			if (Input::GetKeyTrigger(Input::Key::Space) || Input::TriggerPadKey(PAD_INPUT_1))
			{
				tutorial_ = false;
				select_ = 0;
			}
		}
		break;
	case Phase::After:
		pauseFrame_--;
		f = (float)pauseFrame_ / 10;
		size_ = { 1280 * f,720 * f };
		if (pauseFrame_ <= 0)
		{
			isEndGetPause_ = true;
		}
		break;
	default:
		break;
	}
}

void Pause::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(640 - size_.x, 360 - size_.y, 640 + size_.x, 360 + size_.y, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (phase_ == Phase::Middle)
	{
		std::string stageTitle = StageManager::GetInstance()->GetNowLevelNameInjson();

		if (!tutorial_)
		{
			DrawFormatString2FToHandle((WIN_WIDTH / 2) - (float)GetDrawStringWidthToHandle(stageTitle.c_str(), stageTitle.size(), fontHandle_) / 2,150, 0xffffff, 0xff0000, fontHandle_, stageTitle.c_str());
			DrawGraph(440, 350, texturehandleGame_, true);
			DrawGraph(440, 410, texturehandleTutorial_, true);
			DrawGraph(440, 470, texturehandleSelect_, true);
			DrawGraph(440, 530, texturehandleTitle_, true);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
			DrawBox(440,350+select_*60,850, 350 + select_ * 60+50, GetColor(255, 255, 255), false);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		else
		{

		}

	}
}

void Pause::InGameDraw()
{
	DrawGraph(ingamePos_.x, ingamePos_.y,inGameTexturehandle_, true);
}

bool Pause::IsEndGetPause()
{
	return isEndGetPause_;
}

void Pause::StartGetPause()
{
	isEndGetPause_ = false;
	phase_ = Phase::Before;
}
