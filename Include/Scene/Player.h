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
	bool BurialJudge(Object* objct);	//ÉuÉçÉbÉNñÑñvîªíË
	float Easing(const float x) { return 1 - pow(1 - x, 3); }

private:
	enum Direction {
		RIGHT = 1,
		LEFT = -1,
	};

	uint32_t textruehandle_;

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

	const int canJumpTimerMax = 3;
	int canJumpTimer = 1;
	unsigned int color = 0;

	Vector2 inverSize = { 0,0 };
	bool isFront = false;
	const float frameMax = 20.0f;
	float frame = 0.0f;

	Direction direction = Direction::LEFT;
};