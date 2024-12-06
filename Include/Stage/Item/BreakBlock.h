#pragma once

#include "Object.h"
#include "Vector2.h"
#include <cstdint>

class BreakBlock : public Object
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
	/// シェイク
	/// </summary>
	void Shake();
	void ShakeActive();

	/// <summary>
	/// ダメージ
	/// </summary>
	void Damage();

	void OnCollision(Object* object)override;

	/// <summary>
	/// ブロックのHPの取得
	/// </summary>
	int GetBreakBlockHp() { return blockHp_; }

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

	// シェイク
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

	// 画像
	uint32_t hpMaxTexturehandle_;
	uint32_t hpLowTexturehandle_;
};