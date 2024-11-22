#pragma once
#include<Dxlib.h>
#include"Vector2.h"
#include"Object.h"
#include "Water.h"
#include"Key.h"
#include <memory>
#include "ConfettiEmiitter.h"

class Goal: public Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	///  衝突
	/// </summary>
	/// <param name="objct"></param>
	void OnCollision(Object* objct)override;

	void Inversion(const float easing)override;

	void NextSelect();

private:
	std::unique_ptr<ConfettiEmiitter> confettiEmitter;
	bool isUnderWater = false;
	bool isClear = false;
	float speed = 1.0f;
	const float coolTime = 3.0f;
	float timer = coolTime;
	float a = 4.0;
	int key = 1;
	bool isLock;
	float Scale = 1.0;
	int Rot = 0;
	float horizontal = 0.0f;

	uint32_t textruehandle_;
	uint32_t textruehandle2_;
	uint32_t textruehandle3_;
	uint32_t textruehandle4_;
};