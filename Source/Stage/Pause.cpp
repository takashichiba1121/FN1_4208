#include "Pause.h"
#include"TextureManager.h"
#include "DxLib.h"
#include"Input.h"
#include"SceneManager.h"

void Pause::Initialize()
{
	texturehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\PauseTutorial.png");
	texturehandle2_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\PauseTutorial2.png");
	inGameTexturehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\InGameTutorial.png");
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
		if (Input::GetKeyTrigger(Input::Key::X))
		{
			SceneManager::GetInstance()->ChangeScene("TITLE");
		}
		if (Input::GetKeyTrigger(Input::Key::Z))
		{
			SceneManager::GetInstance()->ChangeScene("STAGESELECT");
		}

		//パットはStartだかoptionボタン
		if (Input::GetKeyTrigger(Input::Key::T) || Input::TriggerPadKey(PAD_INPUT_8))
		{
			phase_ = Phase::After;
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
		DrawGraph(363, 240, texturehandle_, true);
		DrawGraph(640, 240, texturehandle2_, true);
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
