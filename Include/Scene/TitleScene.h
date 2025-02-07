#pragma once
#include "BaseScene.h"
#include "Water.h"
#include "TitleLogo.h"
#include "SoundPlayManager.h"

class TitleScene :
    public BaseScene
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	uint32_t textruehandle_key;
	uint32_t textruehandle_pad;
	std::unique_ptr<TitleLogo> titleLogo[3];

	bool drawGuide = false;
	float guideTrans = 0.0f;

	SoundPlayManager* soundPlayManager;
};

