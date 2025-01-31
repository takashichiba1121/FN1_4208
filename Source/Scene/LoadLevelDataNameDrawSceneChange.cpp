#include "LoadLevelDataNameDrawSceneChange.h"
#include <imgui.h>
#include "DxLib.h"
#include "Window.h"
#include <string>
#include "StageManager.h"

LoadLevelDataNameDrawSceneChange::LoadLevelDataNameDrawSceneChange()
{
}

LoadLevelDataNameDrawSceneChange::~LoadLevelDataNameDrawSceneChange()
{
}

void LoadLevelDataNameDrawSceneChange::Initialize()
{


	isStart_ = false;
	isClose_ = false;
	isOpenStart_ = false;
	isEnd_ = false;
	moveTimer_ = 0;
	afterTimer = 0;

	fontHandle_ = CreateFontToHandle("ロンド B スクエア", fontSize_, -1);

}

void LoadLevelDataNameDrawSceneChange::Finalize()
{

}

void LoadLevelDataNameDrawSceneChange::Update()
{
	if (isStart_ && !isEnd_)
	{
		if (!isInBlend_)
		{
			y_ = easeOutQuad(0.0f, 255.0f, moveTimer_ / moveMaxTime_);


			isClose_ = true;

			if (moveTimer_ < moveMaxTime_)
			{
				moveTimer_++;
			}
			else
			{
				isInBlend_ = true;

			}

		}

		if (isOpenStart_ && isInBlend_)
		{
			y_ = easeInQuint(255.0f, 0.0f, afterTimer / afterMaxTime);

			if (afterTimer < afterMaxTime)
			{
				afterTimer++;
			}
			else
			{
				isEnd_ = true;
			}
		}

	}

}

void LoadLevelDataNameDrawSceneChange::Draw()
{
	if (!isEnd_)
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int32_t)y_);	
		DrawFormatString2FToHandle((WIN_WIDTH / 2) - (float)GetDrawFormatStringWidthToHandle(fontHandle_, std::string("ステージ" + std::to_string(StageManager::GetInstance()->GetNowLevelNum() + 1)).c_str()) / 2, (WIN_HEIGHT / 2) - fontSize_, 0xffffff, 0xff0000, fontHandle_, "ステージ%d", StageManager::GetInstance()->GetNowLevelNum() + 1);
		DrawFormatString2FToHandle((WIN_WIDTH / 2) - (float)GetDrawStringWidthToHandle(StageManager::GetInstance()->GetNowLevelNameInjson().c_str(), StageManager::GetInstance()->GetNowLevelNameInjson().size(), fontHandle_) / 2, (WIN_HEIGHT / 2), 0xffffff, 0xff0000, fontHandle_, StageManager::GetInstance()->GetNowLevelNameInjson().c_str());
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}


}