#pragma once

#include <DxLib.h>
#include "Vector2.h"
#include "Object.h"

class LevitationBlock : public Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

private:
	/// <summary>
	/// イージングの関数
	/// </summary>
	float EaseInOutBackP(float t, float b, float c, float d);
	float EaseInOutBack(float x);

private:
	bool isFloatBlock_ = false;
	bool isEasing_ = false;
	int frame_ = 0;
	int maxFrame_ = 25;
	int easingTime_ = 60;
	int difference_ = 70;
	float waterSurface_ = 0.0f;
	float gravity_ = 0.0f;
};