#pragma once
#include"Object.h"
#include"Vector2.h"

class Bubble :
	public Object{

public:

	void Initialize(const Vector2 pos);

	void Update(const float line);

	void Draw();

	void OnCollision(Object* objct)override;

	const bool GetIsDead() { return isDead; }

private:

	Vector2 vector = { 0,3 };
	float size = 0.0f;

	bool isActive = true;
	bool isDead = false;
};