#pragma once
#include"Object.h"
#include"Vector2.h"
#include<string>
class TutorialObject :
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

	void SetJson(nlohmann::json& Level) override;

	void GetJson(nlohmann::json& Level) override;

	void ImGuiEdit()override;

	std::unique_ptr<Object> Clone()override { return std::make_unique<TutorialObject>(*this); };

private:
	bool onCol_;

	bool onColwWindow_;

	Vector2 tutorialSize_ = { 256,128 };

	Vector2 tutorialPos_ = { 0,0 };

	std::string tutorialPadTexture_="Q";
	std::string tutorialKeyTexture_ = "Q";

	uint32_t tutorialPadHandle_=0;

	uint32_t tutorialKeyHandle_ = 0;

	uint32_t textureHandle_ = 0;
};