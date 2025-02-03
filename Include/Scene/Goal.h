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

	void Inversion(const float easing)override;

	void NextSelect();

	float ExpansionGoalText(float x);

	bool GetisLock() { return isLock = true; }
	bool GetisUnLock() { return isLock =false; }

	std::unique_ptr<Object> Clone()override { return std::make_unique<Goal>(*this); };
	
private:
	bool isUnderWater = false;
	bool isClear = false;
	float speed = 1.0f;
	const float coolTime = 3.0f;
	float timer = coolTime;
	float a = 4.0;
	bool isLock;
	float Scale = 1.0;
	int Rot = 0;
	float horizontal = 0.0f;
	float f;
	uint32_t easingFrame_ = 0;
	const uint32_t maxEasingFrame_ = 60;
	int32_t nextStageSelect_ =1;

	//‰æ‘œ
	uint32_t textruehandle_;
	uint32_t textruehandle2_;
	uint32_t textruehandle3_;
	uint32_t textruehandle4_;
	uint32_t textruehandle5_;
	uint32_t textruehandle6_;
	uint32_t textruehandle7_;
};