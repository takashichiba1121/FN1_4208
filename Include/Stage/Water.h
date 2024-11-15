#pragma once
#include<memory>
#include"window.h"
class Water
{
#pragma region Singleton
private:
	Water() {};

	~Water() {};
public:
	Water(const Water& carManager) = delete;

	Water& operator=(const Water& carManager) = delete;

	static Water* GetInstance();
#pragma endregion
public:
	void Update();

	void Inversion(const float easing, bool isfront);

	void Draw();

	void SetHorizontal(float upHorizontal,float dwonHorizontal=720)
	{
		upHorizontal_ = upHorizontal;

		downHorizontal_ = dwonHorizontal;
	}

	float GetHorizontal()
	{
		return upHorizontal_;
	}

private:
	float upHorizontal_ = 160.0f;

	float downHorizontal_ = 720.0f;

	float colA[4] = {0.392f,1.0f,1.0f,0.274f};
	float colB[4] = {0.5f,0.5f,1.0f,0.274f};

	float topPos = 0.0f;
	float underPos = WIN_HEIGHT;
};

