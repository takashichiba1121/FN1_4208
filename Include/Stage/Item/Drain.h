#pragma once
#include"Object.h"

class Drain :
	public Object{

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

	void OnCollision(Object* objct)override;

	void Inversion(const float easing)override;

	std::unique_ptr<Object> Clone()override { return std::make_unique<Drain>(*this); };
private:
	uint32_t drainTexture;
	uint32_t guideTextureKey;
	uint32_t guideTexturePad;
	bool drawGuide = false;
	float guideTrans = 0.0f;
};
