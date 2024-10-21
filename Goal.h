#pragma once
#include<Dxlib.h>
#include"Vector2.h"
#include"Object.h"
class Goal
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	Vector2 pos = { 0,0 };//位置
	Vector2 size = { 10,10 };//大きさ
	int goal;//ゴールの画像

	bool isLock = false;
	bool isUnderWater = false;
	bool isClear = false;
	float speed = 1.0f;
	const float coolTime =3.0f;
	float timer = coolTime;
	float a = 4.0;

	float horizontal = 360.0f;
};

