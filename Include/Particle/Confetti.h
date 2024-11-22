#pragma once
#include"Object.h"
#include"Vector2.h"

class  Confetti :
	public Object {

public:

	~Confetti();

	void Initialize();

	void Update();

	void Draw();

	void OnCollision(Object* objct)override;

	const bool GetIsDead() { return isDead; }

private:

	Vector2 vector = { 0,3 };
	float pos = 0.0f;
	float size = 0.0f;
	int colorR = 0;
	int colorG = 0;
	int colorB = 0;

	bool isActive = true;
	bool isDead = false;
};