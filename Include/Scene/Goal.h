#pragma once
#include<Dxlib.h>
#include"Vector2.h"
#include"Object.h"
#include "Water.h"
#include"Key.h"
#include <memory>

class Goal: public Object
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
	///  �Փ�
	/// </summary>
	/// <param name="objct"></param>
	void OnCollision(Object* objct)override;

	void Inversion(const float easing)override;

private:
	int goal;//�S�[���̉摜
	bool isUnderWater = false;
	bool isClear = false;
	float speed = 1.0f;
	const float coolTime = 3.0f;
	float timer = coolTime;
	float a = 4.0;
	int key = 1;
	bool isLock;
	

	float horizontal = 0.0f;
};