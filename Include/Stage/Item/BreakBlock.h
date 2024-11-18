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
	void ShakeActive();

	/// <summary>
	/// �_���[�W
	/// </summary>
	void Damage();

	/// <summary>
	/// �u���b�N��HP�̎擾
	/// </summary>
	int GetBreakBlockHp() { return blockHp_; }
	void SetBreakBlockHp(int blockHp) { blockHp_ = blockHp; }

private:
	enum BlockHp {
		BLOCK_BROKEN,
		BLOCK_HP_LOW,
		BLOCK_HP_MAX
	};

private:
	int blockHp_ = BLOCK_HP_MAX;
	int damageValue_ = 1;
	bool isBreakBlock_ = false;

	// �V�F�C�N
	int time_ = 0;
	int shakeTime_ = 0;
	const int defaultTime_ = 0;
	int shakeMaxTime_ = 30;
	bool isShake_ = false;
	float shakeMin_ = -5.0f;
	float shakeMax_ = 5.0f;
	Vector2 shakePos_ = { 0.0f,0.0f };
	Vector2 shakeMd_ = { 2.0f,2.0f };
	Vector2 defaultPosition_ = { 0.0f,0.0f };
};