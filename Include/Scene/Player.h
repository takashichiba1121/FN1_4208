#pragma once
#include "Object.h"
#include "BubbleEmitter.h"
#include "SplashEmitter.h"
#include "SoundPlayManager.h"
#include "dxlib.h"
#include <memory>
#include <list>

class Player :
	public Object {

public:

	~Player();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void OnCollision(Object* objct)override;

	float GetSpeed() { return speed; }

	std::unique_ptr<Object> Clone()override { return std::make_unique<Player>(*this); };

private:
	void Operation();	//ëÄçÏ
	void InversionProcess();
	void Move();
	void MoveProcessRight();
	void MoveProcessLeft();
	void Jump();
	void JumpProcess();
	bool BurialJudge(Object* objct);	//ÉuÉçÉbÉNñÑñvîªíË
	float Easing(const float x) { return 1 - pow(1 - x, 3); }

private:
	enum Direction {
		RIGHT,
		LEFT,
	};
	LPCSTR font;
	bool isDrawGuide = false;
	float guideTimerMax = 255.0f;
	float guideTimer = 0.0f;

	uint32_t textruehandle_;

	std::shared_ptr<BubbleEmitter> bubbleEmitter;
	std::shared_ptr<SplashEmitter> splashEmitter;

	const float MaxGravity = 15.0f;
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
	const Vector2 baseSize = { 64,64 };
	bool isFront = false;
	const float frameMax = 20.0f;
	float frame = 0.0f;
	bool isClear = false;

	Direction direction = Direction::RIGHT;
	SoundPlayManager *soundPlayManager;
	bool isBurial = false;
};