#include "SpongeBlock.h"
#include"DxLib.h"
#include"CollisionManager.h"
#include"Water.h"

void SpongeBlock::Initialize()
{
	pos_ = { 640,300 };

	size_ = { 64,64 };

	objectType_ = ObjectType::SPONGE_BLOCK;
	CollisionManager::GetInstance()->AddObject(this);
}

void SpongeBlock::Update()
{
	ObjectUpdate();

	float horizontal = Water::GetInstance()->GetHorizontal();

	if (horizontal > pos_.y + size_.y/2)
	{
		if (isExpansion_)
		{
			isExpansion_ = false;

			size_.x /= scale_.x;

			size_.y /= scale_.y;
		}
	}
	if(horizontal < pos_.y - size_.y/2)
	{
		if (!isExpansion_)
		{
			isExpansion_ = true;

			size_.x *= scale_.x;

			size_.y *= scale_.y;
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
