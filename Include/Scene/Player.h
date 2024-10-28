#pragma once
#include "Object.h"
#include "BubbleEmitter.h"
#include "SplashEmitter.h"
#include <memory>
#include <list>
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

	std::unique_ptr<BubbleEmitter> bubbleEmitter;
	std::unique_ptr<SplashEmitter> splashEmitter;

	const float MaxGravity = 16.0f;
	float initJumpVelocity = -MaxGravity;
	float gravity = 0.0f;
	float declinePercent = 1.0f;

	const float GroundSpeed = 8.0f;
	const float WaterSpeed = GroundSpeed / 1.5f;
	float speed = GroundSpeed;

	bool canJump = false;
	bool isUnderWater = false;
	bool canCrawlUp = false;

	float horizontal = 160.0f;
	float underLine = 700.0f;

	const int canJumpTimerMax = 3;
	int canJumpTimer = 1;
	unsigned int color = 0;
};