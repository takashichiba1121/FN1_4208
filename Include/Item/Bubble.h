#pragma once
#include"Vector2.h"

class Bubble {

public:

	void Initialize(const Vector2 pos);

	void Update(const float line);

	void Draw();

	const bool GetIsDead() { return isDead; }

private:

	Vector2 position = { 0,0 };
	Vector2 vector = { 0,5 };
	Vector2 size = { 8,8 };

	bool isActive = true;
	bool isDead = false;
};