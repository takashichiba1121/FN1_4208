#pragma once

#include <DxLib.h>
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

private:
	bool isBlock_ = false;
};

