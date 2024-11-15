#pragma once
#include"Object.h"
#include"Vector2.h"

class Splash {

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos">�������W</param>
	/// <param name="grv">�����A�㏸���x</param>
	void Initialize(const Vector2 pos, const float grv);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="line">������</param>
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