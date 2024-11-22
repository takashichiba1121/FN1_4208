#pragma once
#include<Dxlib.h>
#include"Vector2.h"
#include"Object.h"
#include "Water.h"
#include"Goal.h"
class Key:public Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	///  衝突
	/// </summary>
	/// <param name="objct"></param>
	void OnCollision(Object* objct)override;



private:
	bool isLock;
};

