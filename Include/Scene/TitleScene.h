#pragma once
#include "BaseScene.h"
#include "Water.h"
#include "TitleLogo.h"

class TitleScene :
    public BaseScene
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	uint32_t textruehandle_;
	std::unique_ptr<TitleLogo> titleLogo[3];

	bool drawGuide = false;
	float guideTrans = 0.0f;
};

