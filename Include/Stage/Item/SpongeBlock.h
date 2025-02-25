#pragma once
#include"Object.h"
#include<memory>
class SpongeBlock :
    public Object
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;
	/// <summary>

	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	void OnCollision(Object* object)override;

	float easeOutCubic(float x);

	float easeInCubic(float x);

	void SetJson(nlohmann::json& Level) override;

	void GetJson(nlohmann::json& Level) override;

	void ImGuiEdit()override;

	void Inversion(const float easing)override;

	std::unique_ptr<Object> Clone()override { return std::make_unique<SpongeBlock>(*this); };

private:

	Vector2 expansion_ = { 3,3 };

	Vector2 initializeSize_={ 64,64 };

	uint32_t easingFrame_=0;

	const uint32_t maxEasingFrame_=20;

	bool isExpansion_ = false;

	bool stopExpansion_ = false;
	
	uint32_t textureHandle_;
};

