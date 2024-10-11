#pragma once
#include<Dxlib.h>
#include"Vector2.h"
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
};

