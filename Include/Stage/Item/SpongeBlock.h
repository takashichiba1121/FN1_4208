#pragma once
#include"Object.h"
#include<memory>
class SpongeBlock :
    public Object
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize()override;
	/// <summary>

	/// XV
	/// </summary>
	void Update()override;

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw()override;

	void OnCollision(Object* object)override;

	float easeOutCubic(float x);

	float easeInCubic(float x);

private:

	Vector2 scale_ = { 3,3 };

	Vector2 initializeSize_={ 64,64 };

	uint32_t easingFrame_=0;

	const uint32_t maxEasingFrame_=60;

	bool isExpansion_ = false;

	bool stopExpansion_ = false;
	
};

