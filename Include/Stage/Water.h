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

	void SetHorizontal(const float horizontal)
	{
		horizontal_ = horizontal;
		tentHorizontal_ = horizontal;
	}

	void SetTentHorizontal(const float horizontal) { tentHorizontal_ = horizontal; }

	float GetHorizontal() { return horizontal_; }
	float GetTentHorizontal() { return tentHorizontal_; }
	bool GetIsChangeHorizontal() { return isChangeHorizontal; }

private:
	const float speed = 5.0f;

	float horizontal_ = 320.0f;
	float tentHorizontal_ = horizontal_;

	float colA[4] = {0.392f,1.0f,1.0f,0.274f};
	float colB[4] = {0.5f,0.5f,1.0f,0.274f};

	float topPos = 0.0f;
	float underPos = WIN_HEIGHT;

	bool isChangeHorizontal = false;
};

