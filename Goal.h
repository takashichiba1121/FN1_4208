#pragma once
#include<Dxlib.h>
#include"Vector2.h"
#include"Object.h"
class Goal
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	Vector2 pos = { 0,0 };//�ʒu
	Vector2 size = { 10,10 };//�傫��
	int goal;//�S�[���̉摜

	bool isLock = false;
	bool isUnderWater = false;
	bool isClear = false;
	float speed = 1.0f;
	const float coolTime =3.0f;
	float timer = coolTime;
	float a = 4.0;

	float horizontal = 360.0f;
};

