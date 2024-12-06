#pragma once
#include<Dxlib.h>
#include"Vector2.h"
#include"Object.h"
#include "Water.h"
#include"Goal.h"
class Key:public Object
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;

	/// <summary>
	///  �Փ�
	/// </summary>
	/// <param name="objct"></param>
	void OnCollision(Object* objct)override;

	bool GetisLock() { return isLock; }
	bool GetisKey() { return isKey; }
private:
	bool isLock = true;
	bool isKey = true;
	bool isGet = false;
	bool isDead = false;
	float rot = 0.0f;
	float s = 0.8f;
	uint32_t textruehandle_;
};

