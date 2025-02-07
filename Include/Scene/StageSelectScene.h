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
	Vector2 GetGraphSize(int32_t GraphHandle);

private:

	int32_t selectStageNum_ = 0;
	int32_t selectStageOldNum_ = 0;

	int32_t titleTextruehandle_ = 0;

	//イージング用の引数
	float moveTime_ = 0;
	float movemaxTime_ = 20;


	bool isNext_ = false;
	bool isTitleExit_ = false;
	float moveNextTime_ = 0;
	float moveNextmaxTime_ = 50;

	float padMoveWait_ = 0;
	float padMoveMaxWait_ = 10;

	Vector2 titleTextPos_;
	Vector2 titleTextSize_ = { 0.5f,0.5f };

	LevelPreView nextPreview_;

	std::list<LevelPreView>  previews_;

	SoundPlayManager* soundPlayManager;

	float colA[4] = { 0.392f,1.0f,1.0f,0.274f };
	float colB[4] = { 0.5f,0.5f,1.0f,0.274f };

};