#include "Key.h"
#include "Input.h"
#include "CollisionManager.h"

Key::~Key()
{
	CollisionManager::GetInstance()->RemoveObject(this);
}

void Key::Initialize()
{
	pos_ = { 1000.0f,400.0f };
	size_ = { 64.0f,64.0f };
	objectType_ = ObjectType::KEY;
	CollisionManager::GetInstance()->AddObject(this);

	isLock = true;
}

void Key::Update()
{
}

void Key::Draw()
{
	//Мо
	if (isCollision_ == true) {
		DrawBox(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f,
			pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f,
			GetColor(255, 255, 0), TRUE);
		DrawFormatString(pos_.x - 15, pos_.y - 10, GetColor(0, 0, 0), "key");
	}
}

void Key::OnCollision(Object* objct)
{
	if (objct->GetObjectType() == ObjectType::PLAYER) {
		DrawFormatString(0, 150, GetColor(0, 255, 0), "get");
		isCollision_ = false;
	}
}
