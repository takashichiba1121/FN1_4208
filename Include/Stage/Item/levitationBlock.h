#pragma once

#include <DxLib.h>
#include "Vector2.h"
#include "Object.h"

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

private:
	/// <summary>
	/// �C�[�W���O�̊֐�
	/// </summary>
	/// <param name="t">����</param>
	/// <param name="b">�J�n�ʒu</param>
	/// <param name="c">�J�n�ʒu - �I���ʒu</param>
	/// <param name="d">���v����</param>
	/// <returns></returns>
	float EaseInOutBackP(float t, float b, float c, float d);
	float EaseInOutBack(float x);

private:
	bool isFloatBlock_ = false;
	float gravity_ = 0.0f;
	int frame_ = 0;
};