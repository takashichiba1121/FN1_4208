#pragma once

#include "Object.h"
#include "Vector2.h"

class BreakBlock : public Object
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;

	/// <summary>
	/// �V�F�C�N
	/// </summary>
	void Shake();

private:
	enum BlockHp {
		BlockBroken,
		BlockHpLow,
		BlockHpMax
	};

private:
	bool isBreakBlock_ = false;
	int blockHp_ = 2;
	int shakeTime_ = 0;
	int shakeMaxTime_ = 20;
	float shakeMin_ = -5.0f;
	float shakeMax_ = 5.0f;
	float shakePosX_ = 0.0f;
	float shakeMdX_ = 2.0f;
	float defaultPosition_ = 0.0f;
};
