#include "water.h"
#include"Input.h"
#include"imgui.h"

void Water::Update()
{
#ifdef _DEBUG

	//Å™Å´ÉLÅ[Ç≈êÖïΩê¸í≤êﬂ
	if (Input::GetKey(Input::Key::Up)) {
		horizontal_ -= 2.0f;
	}
	if (Input::GetKey(Input::Key::Down)) {
		horizontal_ += 2.0f;
	}

	ImGui::Begin("Water");



	ImGui::ColorEdit4("WaterCol",col );

	ImGui::End(); 
#endif
}

void Water::Draw()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, col[3]*255);
	DrawBox(0,horizontal_,1280,720, GetColor(col[0]*255,col[1]*255, col[2]*255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawLine(0, (int)horizontal_, 1280, (int)horizontal_, GetColor(100, 255, 255));


}
