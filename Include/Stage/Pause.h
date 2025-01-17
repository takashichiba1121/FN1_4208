#pragma once
#include<memory>
#include"Vector2.h"
class Pause
{
	enum class Phase
	{
		Before,
		Middle,
		After,
	};
public:

	void Initialize();

	void Update();

	void Draw();

	bool IsEndGetPause();

	void StartGetPause();
private:
	uint32_t texturehandle_=0;
	uint32_t texturehandle2_ = 0;

	Phase phase_ = Phase::Before;

	Vector2 size_ = {0,0};

	uint32_t pauseFrame_=0;

	bool isEndGetPause_=false;
};

