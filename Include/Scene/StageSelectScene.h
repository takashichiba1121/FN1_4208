#pragma once
#include "BaseScene.h"
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

	std::vector<std::string> stageFileName_;

	int32_t selectStageNum_ = 0;

};