#pragma once
#include "Object.h"

class Player :
	public Object {

public:

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void OnCollision(Object* objct)override;

	float GetSpeed() { return speed; }

private:
	void Operation();	//ëÄçÏ
	void Move();
	void Jump();

private:

	Vector2 pos_ = { 0,0 };
	Vector2 size_ = { 32,64 };
	Vector2 moveVal = { 0,0 };

	const float MaxGravity = 16.0f;
	float initJumpVelocity = -MaxGravity;
	float gravity = 0.0f;
	float declinePercent = 1.0f;

	const float GroundSpeed = 8.0f;
	const float WaterSpeed = GroundSpeed / 1.5f;
	float speed = GroundSpeed;

	bool canJump = false;
	bool isOnFloor = false;
	bool isUnderWater = false;
	bool canCrawlUp = false;

	float horizontal = 160.0f;
	float underLine = 700.0f;

};