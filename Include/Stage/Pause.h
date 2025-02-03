#pragma once
#include<memory>
#include"Vector2.h"
#include"SoundPlayManager.h"
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

	void InGameUpdate();

	void Update();

	void Draw();

	void InGameDraw();

	bool IsEndGetPause();

	void StartGetPause();
private:
	uint32_t texturehandleTitle_ = 0;
	uint32_t texturehandleGame_ = 0;
	uint32_t texturehandleTutorial_ = 0;
	uint32_t texturehandleSelect_ = 0;

	uint32_t inGameTextureKeyHandle_ = 0;
	uint32_t inGameTexturePadHandle_ = 0;

	Phase phase_ = Phase::Before;

	Vector2 size_ = { 0,0 };

	uint32_t pauseFrame_ = 0;

	bool isEndGetPause_ = false;

	bool notPlay_ = false;

	uint32_t inGameUIFrame_ = 0;

	const uint32_t inGameUIMaxFrame_ = 60;

	Vector2 ingamePos_ = { 0,0 };

	SoundPlayManager* soundPlayManager;

	int16_t select_ = 0;

	uint16_t alpha_ = 255;

	bool isAlphaPlas_ = false;

	bool tutorial_ = false;

	uint32_t fontHandle_=0;

	uint32_t fontSize_=128;
};

