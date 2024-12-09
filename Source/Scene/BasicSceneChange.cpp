#include "BasicSceneChange.h"
#include <imgui.h>
#include "DxLib.h"
#include "Window.h"
#include <cstdint>

BasicSceneChange::BasicSceneChange()
{
}

BasicSceneChange::~BasicSceneChange()
{
}

void BasicSceneChange::Initialize()
{
	

	isStart_ = false;
	isClose_ = false;
	isOpenStart_ = false;
	isEnd_ = false;
	moveTimer_ = 0;
	afterTimer = afterMaxTime;

}

void BasicSceneChange::Finalize()
{

}

void BasicSceneChange::Update()
{
	if (isStart_ && !isEnd_)
	{
		if (!isClose_)
		{
			y_ = easeOutQuad((float)WIN_HEIGHT, 0.0f, moveTimer_ / moveMaxTime_);

			


			if (moveTimer_ < moveMaxTime_)
			{
				moveTimer_++;
			}
			else
			{
				isClose_ = true;

			}


		}

		if (isOpenStart_)
		{
			y_ = easeInQuint(0.0f, (float)WIN_HEIGHT, afterTimer / afterMaxTime);

			if (afterTimer > 0)
			{
				afterTimer--;
			}
			else
			{
				isEnd_ = true;
			}
		}

	}

}

void BasicSceneChange::Draw()
{
	if (!isEnd_)
	{
		
		DrawBoxAA(0.0f, y_,(float)WIN_WIDTH, (float)WIN_HEIGHT, GetColor((int32_t)0.392f, (int32_t)1.0f, (int32_t)1.0f), true);
		
	}


}