#pragma once

#include "Vector2.h"
#include "Object.h"
#include <cstdint>

class LevitationBlock : public Object
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

	void OnCollision(Object* objct)override;

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	void Inversion(const float easing)override;

	std::unique_ptr<Object> Clone()override { return std::make_unique<LevitationBlock>(*this); };

private:
	/// <summary>
	/// イージングの関数
	/// </summary>
	float EaseInOutBackP(float t, float b, float c, float d);
	float EaseInOutBack(float x);

private:
	int frame_ = 0;
	int maxFrame_ = 5;
	int easingTime_ = 60;
	int easingCount_ = 1;
	int difference_ = 70;
	bool isFloatBlock_ = false;
	bool isEasing_ = false;
	float waterSurface_ = 0.0f;
	float gravity_ = 0.0f;
	bool onGround_ = false;
	bool onLevitation_ = false;
	
	uint32_t textureHandle_;
};