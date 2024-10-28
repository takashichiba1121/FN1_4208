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

	void SetHorizontal(float horizontal)
	{
		horizontal_ = horizontal;
	}

	float GetHorizontal()
	{
		return horizontal_;
	}
private:
	float horizontal_ = 160.0f;

	float col[4] = {0.392f,1.0f,1.0f,0.274f};
};

