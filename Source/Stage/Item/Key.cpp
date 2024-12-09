#include "Key.h"
#include "Input.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "StageManager.h"


void Key::Initialize()
{
	pos_ = { 1000.0f,400.0f };
	size_ = { 64.0f,64.0f };
	objectType_ = ObjectType::KEY;
	isExclude_ = false;
	CollisionManager::GetInstance()->AddObject(this);

	//‰æ‘œ“Ç‚İ‚İ
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Key.png");

	isLock = true;
	isKey = true;
}

void Key::Update()
{	
	ObjectUpdate();
	//Œ®æ‚Á‚½‚ç
	if (isGet) {
		//‰ñ“]
		rot += 0.2f;
		//k¬
		if (s >= 0.0f) {
			s -= 0.02f;
		}
		else {
			isDead = true;
		}
	}
	//else {
	//	//isCollision_ = true;
	//}
}

void Key::Draw()
{
	//Œ®
	if (isDead==false) {
		DrawRotaGraph3(pos_.x, pos_.y, size_.x / 2, size_.y / 2, s, s,rot, textruehandle_, TRUE);
		//DrawFormatString(pos_.x - 15, pos_.y - 10, GetColor(0, 0, 0), "key");
	}
}

void Key::OnCollision(Object* objct)
{
	if (objct->GetObjectType() == ObjectType::PLAYER) {
		isGet = true;
		isLock = false;
		isKey = false;
		StageManager::GetInstance()->GetKey();
	}
}
