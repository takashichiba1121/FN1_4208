#pragma once

#include "Vector2.h"
#include "Object.h"

class Block : public Object
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

	void Inversion(const float easing)override;

private:
	bool isBlock_ = false;

	uint32_t textureHandle_;
};

