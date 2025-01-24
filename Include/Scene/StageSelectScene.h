#pragma once
#include "BaseScene.h"
#include "LevelPreview.h"
#include "SoundPlayManager.h"
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

	Vector2 easeInQuad(Vector2 start, Vector2 end, float time);

private:

	int32_t selectStageNum_ = 0;
	int32_t selectStageOldNum_ = 0;

	//イージング用の引数
	float moveTime_ = 0;
	float movemaxTime_ = 30;


	bool isNext_ = false;
	float moveNextTime_ = 0;
	float moveNextmaxTime_ = 50;

	float padMoveWait_ = 0;
	float padMoveMaxWait_ = 10;

	Vector2 titleTextPos_;

	LevelPreView nextPreview_;

	std::list<LevelPreView>  previews_;

	SoundPlayManager* soundPlayManager;

};