#pragma once

#include "Vector2.h"
#include "Object.h"

class Block : public Object
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

	void Inversion(const float easing)override;

private:
	bool isBlock_ = false;

	uint32_t textureHandle_;
};

