#pragma once
#include<Dxlib.h>
#include"Vector2.h"
#include"Object.h"
#include "Water.h"
class Goal: public Object
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
	///  衝突
	/// </summary>
	/// <param name="objct"></param>
	void OnCollision(Object* objct)override;

	void Inversion()override;

private:
	int goal;//ゴールの画像

	bool isLock = false;
	bool isUnderWater = false;
	bool isClear = false;
	float speed = 1.0f;
	const float coolTime = 3.0f;
	float timer = coolTime;
	float a = 4.0;

	float horizontal = 0.0f;
};