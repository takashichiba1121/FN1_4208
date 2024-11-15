#include "water.h"
#include"Input.h"
#include"imgui.h"

void Water::Update()
{
#ifdef _DEBUG

	//Å™Å´ÉLÅ[Ç≈êÖïΩê¸í≤êﬂ
	if (Input::GetKey(Input::Key::Up)) {
		upHorizontal_ -= 2.0f;
	}
	if (Input::GetKey(Input::Key::Down)) {
		upHorizontal_ += 2.0f;
	}

	if (Input::GetKeyTrigger(Input::Key::Q))
	{
		downHorizontal_ = upHorizontal_;

		upHorizontal_ = 0;

	}

	ImGui::Begin("Water");



	ImGui::ColorEdit4("WaterCol",col );

	ImGui::End(); 
#endif

	if (downHorizontal_<720)
	{
		upHorizontal_+=10;

		downHorizontal_+=10;
	}
	else if(downHorizontal_ > 720)
	{
		upHorizontal_ += downHorizontal_-upHorizontal_;

		downHorizontal_ = 720;
	}
}

void Water::Draw()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, col[3]*255);
	DrawBox(0,upHorizontal_,1280, downHorizontal_, GetColor(col[0]*255,col[1]*255, col[2]*255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawLine(0, (int)upHorizontal_, 1280, (int)upHorizontal_, GetColor(100, 255, 255));
}

Water* Water::GetInstance()
{
	static Water instance;
	return &instance;
}
