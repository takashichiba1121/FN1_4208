#pragma once

#include <DxLib.h>
#include "Vector2.h"
#include "Object.h"
#include "Water.h"

class LevitationBlock : public Object
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
	/// �ړ�
	/// </summary>
	void Move();

private:
	/// <summary>
	/// �C�[�W���O�̊֐�
	/// </summary>
	float EaseInOutBackP(float t, float b, float c, float d);
	float EaseInOutBack(float x);

private:
	bool isFloatBlock_ = false;
	bool isEasing_ = false;
	int frame_ = 0;
	int maxFrame_ = 25;
	int easingTime_ = 60;
	int difference_ = 70;
	float waterSurface_ = 0.0f;
	float gravity_ = 0.0f;
};