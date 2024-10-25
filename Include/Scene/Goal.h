#pragma once
#include<Dxlib.h>
#include"Vector2.h"
#include"Object.h"
class Goal: public Object
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// XV
	/// </summary>
	void Update()override;

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw()override;

	/// <summary>
	///  Õ“Ë
	/// </summary>
	/// <param name="objct"></param>
	void OnCollision(Object* objct)override;
private:
	int goal;//ƒS[ƒ‹‚Ì‰æ‘œ

	bool isLock = false;
	bool isUnderWater = false;
	bool isClear = false;
	float speed = 1.0f;
	const float coolTime = 3.0f;
	float timer = coolTime;
	float a = 4.0;

	float horizontal = 160.0f;
};