#pragma once
#include"Object.h"
class TutorialObject :
	public Object
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;
	/// <summary>

	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;

	void OnCollision(Object* object)override;

	void SetJson(nlohmann::json& Level) override;

	void GetJson(nlohmann::json& Level) override;

	void ImGuiEdit()override;

private:

};