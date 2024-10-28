#pragma once
#include"Splash.h"
#include <memory>
#include <list>

class SplashEmitter {

public:

	void Initialize(const int timer);

	void Update(const Vector2 pos);

	void Draw();

	void SetHorizontal(const float line) { horizontal = line; }

private:

	std::list<std::unique_ptr<Splash>> splash_;

	Vector2 pos;

	float horizontal = 0.0f;

	int maxTimer = 0;
	int emitTimer = 60;
};