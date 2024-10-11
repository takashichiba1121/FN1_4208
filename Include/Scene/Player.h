#pragma once
#include "Vector2.h"

class Player {

public:

	void Initialize();
	void Update();
	void Draw();

private:
	void Operation();	//ëÄçÏ
	void Move();
	void Jump();

private:

	Vector2 pos = { 0,0 };
	Vector2 size = { 64,64 };

	const float MaxGravity = 20.0f;
	const float InitJumpVelocity = -MaxGravity;
	float gravity = 0.0f;

	const float groundSpeed = 8.0f;
	const float waterSpeed = groundSpeed / 1.5f;
	float speed = groundSpeed;

	bool isJump = false;
	bool isCanJump = false;
	bool isOnFloor = false;
	bool isUnderWater = false;

	float horizontal = 360.0f;
};