#include "NoneSceneChange.h"
#include <imgui.h>
#include "DxLib.h"
#include "Window.h"
#include <cstdint>

NoneSceneChange::NoneSceneChange()
{
}

NoneSceneChange::~NoneSceneChange()
{
}

void NoneSceneChange::Initialize()
{


	isStart_ = false;
	isClose_ = false;
	isOpenStart_ = false;
	isEnd_ = false;

}

void NoneSceneChange::Finalize()
{

}

void NoneSceneChange::Update()
{
	if (isStart_ && !isEnd_)
	{
		if (!isClose_)
		{		
			isClose_ = true;	
		}

		if (isOpenStart_)
		{
			isEnd_ = true;
		}

	}

}

void NoneSceneChange::Draw()
{


}