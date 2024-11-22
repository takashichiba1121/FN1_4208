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
	/// ‰Šú‰»
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// XV
	/// </summary>
	void Update() override;

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
	bool isLock;
};

