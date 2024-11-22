#pragma once
#include"Object.h"
#include<memory>
class SpongeBlock :
    public Object
{
public:
	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize()override;
	/// <summary>

	/// çXêV
	/// </summary>
	void Update()override;

	/// <summary>
	/// ï`âÊ
	/// </summary>
	void Draw()override;

	void OnCollision(Object* object)override;

	float easeOutCubic(float x);

	float easeInCubic(float x);

	void a(nlohmann::json& Level) override;

	void b(nlohmann::json& Level) override;

	void DragFloat2()override;

private:

	Vector2 expansion_ = { 1,1 };

	Vector2 initializeSize_={ 64,64 };

	uint32_t easingFrame_=0;

	const uint32_t maxEasingFrame_=60;

	bool isExpansion_ = false;

	bool stopExpansion_ = false;
	
};

