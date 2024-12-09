#include "BasicSceneChange.h"
#include <imgui.h>

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
	angle_ = 0;
	scale_ = 1;
	scaleTimer_ = 0;
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
			scale_ = DirectXpre::easeOutQuad(0.01f, 20.0f, scaleTimer_ / scaleMaxTime_);

			chengSprite_.scale_ = Vector2(scale_, scale_);
			chengSprite_.rotate_ = angle_;
			chengSprite_.Update();


			if (scaleTimer_ < scaleMaxTime_)
			{
				scaleTimer_++;
				angle_ += rotSpeed_;
			}
			else
			{
				isClose_ = true;

			}


		}

		if (isOpenStart_)
		{
			alpha_ = DirectXpre::easeInQuint(0.0f, 1.0f, afterTimer / afterMaxTime);

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
		chengSprite_.Draw();
	}


}