#include "SpongeBlock.h"
#include"DxLib.h"
#include"CollisionManager.h"
#include"Water.h"
#include"Inversion.h"
#include<cmath>
#include"imgui.h"

void SpongeBlock::Initialize()
{
	pos_ = { 640,600 };

	size_ = initializeSize_;

	objectType_ = ObjectType::SPONGE_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);
}

void SpongeBlock::Update()
{
	ObjectUpdate();

	float horizontal = Water::GetInstance()->GetHorizontal();

	if (horizontal > pos_.y + size_.y / 2)
	{
		if (isExpansion_)
		{
			isExpansion_ = false;

			stopExpansion_ = false;
		}
	}
	if (horizontal < pos_.y - size_.y / 2)
	{
		if (!isExpansion_)
		{
			isExpansion_ = true;

			stopExpansion_ = false;
		}
	}

	if (!Inversion::GetInstance()->GetIsInversion()&&!stopExpansion_)
	{
		if (isExpansion_ && easingFrame_ < maxEasingFrame_)
		{
			easingFrame_++;

			float f = easeInCubic(static_cast<float>(easingFrame_) / static_cast<float>(maxEasingFrame_));

			size_ = (initializeSize_ * expansion_ - initializeSize_) * f;
			size_ += initializeSize_;
		}
		else if (!isExpansion_ && easingFrame_ > 0)
		{
			easingFrame_--;

			float f = easeInCubic(static_cast<float>(easingFrame_) / static_cast<float>(maxEasingFrame_));

			size_ = (initializeSize_ * expansion_ - initializeSize_) * f;
			size_ += initializeSize_;
		}
	}
}

void SpongeBlock::Draw()
{
	DrawBox(
		(int)(pos_.x - size_.x / 2.0f), (int)(pos_.y - size_.y / 2.0f),
		(int)(pos_.x + size_.x / 2.0f), (int)(pos_.y + size_.y / 2.0f),
		GetColor(255, 255, 0), TRUE);
}

void SpongeBlock::OnCollision(Object* object)
{

	pos_ = oldPos_;
	if (objectType_ < object->GetObjectType()&&isExclude_&&object->IsExclude())
	{
		Vector2 posA = object->GetPos();
		Vector2 sizeA = object->GetSize();
		Vector2 oldSizeA = object->GetOldSize();
		Vector2 oldPosA = object->GetOldPos();

		Vector2 move = { 0,0 };

		Vector2 oldMove = { 0,0 };

		if (posA.y < pos_.y)
		{
			move.y = (pos_.y - size_.y / 2) - (posA.y + sizeA.y / 2);

			oldMove.y = (oldPos_.y - oldSize_.y / 2) - (oldPosA.y + oldSizeA.y / 2);
		}
		else
		{
			move.y = (posA.y - sizeA.y / 2) - (pos_.y + size_.y / 2);

			oldMove.y = (oldPosA.y - oldSizeA.y / 2) - (oldPos_.y + oldSize_.y / 2);
		}

		if (posA.x < pos_.x)
		{
			move.x = (posA.x + sizeA.x / 2) - (pos_.x - size_.x / 2);

			oldMove.x = (oldPosA.x + oldSizeA.x / 2) - (oldPos_.x - oldSize_.x / 2);
		}
		else
		{
			move.x = (posA.x - sizeA.x / 2) - (pos_.x + size_.x / 2);

			oldMove.x = (oldPosA.x - oldSizeA.x / 2) - (oldPos_.x + oldSize_.x / 2);
		}

		if (move.x > 0 && oldMove.x > 0 || move.x < 0 && oldMove.x < 0)
		{
			move.x = 0;

			oldMove.x = 0;
		}
		if (move.y > 0 && oldMove.y > 0 || move.y < 0 && oldMove.y < 0)
		{
			move.y = 0;

			oldMove.y = 0;
		}
		size_ += move;
		stopExpansion_ = true;
	}
}

float SpongeBlock::easeOutCubic(float x)
{
	return 1 - pow(1 - x, 3);
}

float SpongeBlock::easeInCubic(float x)
{
	return 1 - cos((x * 3.141592) / 2);;
}

void SpongeBlock::SetJson(nlohmann::json& Level)
{
	Level["Expansion"]= { expansion_.x,expansion_.y };
}

void SpongeBlock::GetJson(nlohmann::json& Level)
{
	expansion_.x = Level["Expansion"][0];
	expansion_.y = Level["Expansion"][1];
}

void SpongeBlock::DragFloat2()
{
	float v[2] = { expansion_.x,expansion_.y };

	ImGui::DragFloat2("expansion", v, 1.0f, 1.0f, 1000.0f);

	expansion_ = {v[0],v[1]};
}
