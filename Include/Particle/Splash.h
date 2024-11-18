#pragma once
#include"Object.h"
#include"Vector2.h"

class Splash {

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">初期座標</param>
	/// <param name="grv">落下、上昇速度</param>
	void Initialize(const Vector2 pos, const float grv);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="line">水平線</param>
	void Update(const float line);

	void Draw();

	const bool GetIsDead() { return isDead; }

private:

	Vector2 position = { 0,0 };
	Vector2 vector = { 0,0 };

	const float MaxGravity = 16.0f;
	const float MinSize = 2.0f;
	const float MaxVecX = 2.0f;
	const float Accel = 0.2f;

	float size = 1.0f;

	bool isDead = false;

	unsigned int color;
};