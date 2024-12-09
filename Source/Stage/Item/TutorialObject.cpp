#include"TutorialObject.h"
#include"CollisionManager.h"
#include"DxLib.h"
#include"Collision.h"
#include"imgui.h"
#include"TextureManager.h"

void TutorialObject::Initialize()
{
	pos_ = { 300,686 };

	size_ = {64,64};

	isExclude_ = false;
	objectType_ = ObjectType::TUTORIAL;
	CollisionManager::GetInstance()->AddObject(this);

	tutorialHandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\"+ tutorialTexture_ +".png");

	// ‰æ‘œ“Ç‚Ýž‚Ý
	textureHandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Tutorial.png");

	GetGraphSizeF(tutorialHandle_,&tutorialSize_.x,&tutorialSize_.y);
}

void TutorialObject::Update()
{
	ObjectUpdate();

	onCol_ = false;

	tutorialPos_ = { pos_.x,pos_.y - (tutorialSize_.y / 2) - (size_.y / 2) - 10 };
}

void TutorialObject::Draw()
{
	// ƒuƒƒbƒN‚Ì•`‰æ
	DrawRotaGraph3F(
		pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f,
		(double)(size_.x / 64.0), (double)(size_.y / 64.0), 0.0, textureHandle_, true);
	if (onCol_)
	{
		if (onColwWindow_)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			//DrawBox(
			//	(int)(tutorialPos_.x - tutorialSize_.x / 2.0f), (int)(tutorialPos_.y - tutorialSize_.y / 2.0f),
			//	(int)(tutorialPos_.x + tutorialSize_.x / 2.0f), (int)(tutorialPos_.y + tutorialSize_.y / 2.0f),
			//	GetColor(255, 255, 0), TRUE);

			DrawGraph((int)(tutorialPos_.x - tutorialSize_.x / 2.0f), (int)(tutorialPos_.y - tutorialSize_.y / 2.0f),
				tutorialHandle_, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
		{

			//DrawBox(
			//	(int)(tutorialPos_.x - tutorialSize_.x / 2.0f), (int)(tutorialPos_.y - tutorialSize_.y / 2.0f),
			//	(int)(tutorialPos_.x + tutorialSize_.x / 2.0f), (int)(tutorialPos_.y + tutorialSize_.y / 2.0f),
			//	GetColor(255, 255, 0), TRUE);

			DrawGraph((int)(tutorialPos_.x - tutorialSize_.x / 2.0f), (int)(tutorialPos_.y - tutorialSize_.y / 2.0f),
				tutorialHandle_, true);
		}
	}
}

void TutorialObject::OnCollision(Object* object)
{
	onCol_ = true;

	if (object->GetObjectType()==ObjectType::PLAYER)
	{
		Object window;

		window.SetPos(tutorialPos_);
		window.SetSize(tutorialSize_);

		onColwWindow_=Collision::AABB(object, &window);
	}
}

void TutorialObject::SetJson(nlohmann::json& Level)
{
	Level["tutorialTexture"] = tutorialTexture_;
}

void TutorialObject::GetJson(nlohmann::json& Level)
{
	tutorialTexture_ = Level["tutorialTexture"].get<std::string>();
}

void TutorialObject::ImGuiEdit()
{
	char buf[255]{};

	strncpy_s(buf, tutorialTexture_.c_str(), sizeof(buf) - 1);

	ImGui::InputText("TextureName", buf, sizeof(buf));

	tutorialTexture_ = buf;
}
