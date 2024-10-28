#pragma once
#include"Object.h"
#include"Vector2.h"

class Splash {

public:

	void Initialize(const Vector2 pos);

	void Update(const float line);

	void Draw();

	const bool GetIsDead() { return isDead; }

private:

	Vector2 position = { 0,0 };
	Vector2 vector = { 0,0 };
	float size = 1.0f;
	int deathTimer = 30;
	bool isActive = true;
	bool isDead = false;
};