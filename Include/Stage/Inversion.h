#pragma once
#include"cmath"
#include<memory>

class Inversion {

#pragma region Singleton

public:

	Inversion() {};

	Inversion(const Inversion& carManager) = delete;

	Inversion& operator=(const Inversion& carManager) = delete;

	static Inversion* GetInstance();
#pragma endregion

public:

	void Update();

	bool GetIsInversion() { return isInversion; }
	bool GetIsFront() { return isFront; }

private:

	float Easing(const float x) { return x < 0.5 ? 16 * x * x * x * x * x : 1 - (float)pow(-2 * x + 2, 5) / 2; }

private:

	const float MaxFrame = 60.0f;
	float frame = 0.0f;

	float horizontalPos = 0.0f;
	float easeStartPos = 0.0f;
	float easeEndPos = 0.0f;

	bool isInversion = false;
	bool isFront = true;
};