#pragma once
#include"Object.h"

class Drain :
	public Object{

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

	void OnCollision(Object* objct)override;

	void Inversion(const float easing)override;

private:

	int color;
};
