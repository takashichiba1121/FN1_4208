#pragma once

#include <DxLib.h>
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

private:
	bool isBlock_ = false;
};

