#pragma once
#include<Dxlib.h>
#include"Vector2.h"
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
};

