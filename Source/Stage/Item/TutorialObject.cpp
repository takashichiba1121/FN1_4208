#include"TutorialObject.h"
#include"CollisionManager.h"

void TutorialObject::Initialize()
{
	pos_ = { 300,686 };

	size_ = {64,64};

	isExclude_ = false;
	objectType_ = ObjectType::SPONGE_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);
}

void TutorialObject::Update()
{
	ObjectUpdate();
}

void TutorialObject::Draw()
{
}

void TutorialObject::OnCollision(Object* object)
{
}

void TutorialObject::SetJson(nlohmann::json& Level)
{
	//Level["Expansion"] = { expansion_.x,expansion_.y };
}

void TutorialObject::GetJson(nlohmann::json& Level)
{
	//expansion_.x = Level["Expansion"][0];
	//expansion_.y = Level["Expansion"][1];
}

void TutorialObject::ImGuiEdit()
{
	//float v[2] = { expansion_.x,expansion_.y };

	//ImGui::DragFloat2("expansion", v, 1.0f, 1.0f, 1000.0f);

	//expansion_ = { v[0],v[1] };
}
