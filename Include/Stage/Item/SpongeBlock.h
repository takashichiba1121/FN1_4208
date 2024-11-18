#pragma once
#include"Object.h"
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



private:

	Vector2 scale_ = { 3,3 };

	bool isExpansion_ = false;
	
};

