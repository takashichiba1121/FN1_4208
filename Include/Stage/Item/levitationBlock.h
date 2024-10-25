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

private:
	/// <summary>
	/// イージングの関数
	/// </summary>
	/// <param name="t">時間</param>
	/// <param name="b">開始位置</param>
	/// <param name="c">開始位置 - 終了位置の差</param>
	/// <param name="d">合計時間</param>
	/// <returns></returns>
	float EaseInOutBackP(float t, float b, float c, float d);
	float EaseInOutBack(float x);

private:
	bool isFloatBlock_ = false;
	bool isEasing_ = false;
	int frame_ = 0;
	int waterSurface_ = 0;
	float gravity_ = 0.0f;
};