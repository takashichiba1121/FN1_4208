#pragma once
#include<memory>
class Water
{
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

	float col[4] = {0.392,1.0f,1.0f,0.274};
};

