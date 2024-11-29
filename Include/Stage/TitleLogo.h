#pragma once
#include "Water.h"
#include "Vector2.h"

class TitleLogo {

public:

	void Initialize(const int num);

	void Update();

	void Draw();

	void SetPos(const Vector2 pos) { pos_ = pos; }

private:

	float EaseInOut(float x){ return -(cos(3.14f * x) - 1) / 2; }

	const float frameMax = 120.0f;
	float frame;
	float easepos_;
	bool updown = true;

	uint32_t textruehandle_;

	const Vector2 textureSize = {256,256};
	Vector2 pos_;
	Vector2 size_;
	int sheetNum;


};