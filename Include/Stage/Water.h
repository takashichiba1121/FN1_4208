#pragma once
#include<memory>
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

	float col[4] = {0.392f,1.0f,1.0f,0.274f};
};

