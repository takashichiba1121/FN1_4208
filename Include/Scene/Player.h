#pragma once
#include "Object.h"

class Player :
	public Object {

public:

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void OnCollision(Object* objct)override;

private:
	void Operation();	//ëÄçÏ
	void Move();
	void Jump();

private:

	Vector2 pos_ = { 0,0 };
	Vector2 size_ = { 64,64 };

	const float MaxGravity = 16.0f;
	float initJumpVelocity = -MaxGravity;
	float gravity = 0.0f;

	const float groundSpeed = 8.0f;
	const float waterSpeed = groundSpeed / 1.5f;
	float speed = groundSpeed;

	bool canJump = false;
	bool isOnFloor = false;
	bool isUnderWater = false;
	bool canCrawlUp = false;

	float horizontal = 360.0f;
};