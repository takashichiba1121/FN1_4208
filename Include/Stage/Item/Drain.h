#pragma once
#include"Object.h"

class Drain :
	public Object{

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

	void OnCollision(Object* objct)override;

	void Inversion(const float easing)override;

private:

	int color;
};
