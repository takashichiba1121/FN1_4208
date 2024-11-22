#pragma once
#include "BaseScene.h"
#include "LevelPreview.h"
#include <memory>
#include <vector>
#include <string>


class StageSelectScene :public BaseScene
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:

	int32_t selectStageNum_ = 0;

	LevelPreView preview1_;

};