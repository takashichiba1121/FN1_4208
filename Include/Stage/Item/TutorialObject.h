#pragma once
#include"Object.h"
#include"Vector2.h"
#include<string>
class TutorialObject :
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

	void SetJson(nlohmann::json& Level) override;

	void GetJson(nlohmann::json& Level) override;

	void ImGuiEdit()override;

private:
	bool onCol_;

	bool onColwWindow_;

	Vector2 tutorialSize_ = { 256,128 };

	Vector2 tutorialPos_ = { 0,0 };

	std::string tutorialTexture_="Q";

	uint32_t tutorialHandle_=0;

	uint32_t textureHandle_ = 0;
};