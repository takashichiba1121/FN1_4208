#include "Key.h"
#include "Input.h"
#include "CollisionManager.h"
#include "TextureManager.h"


void Key::Initialize()
{
	pos_ = { 1000.0f,400.0f };
	size_ = { 64.0f,64.0f };
	objectType_ = ObjectType::KEY;
	CollisionManager::GetInstance()->AddObject(this);

	//‰æ‘œ“Ç‚Ýž‚Ý
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Key.png");

	isLock = true;
}

void Key::Update()
{
	//Œ®Žæ‚Á‚½‚ç
	if (isGet) {
		//‰ñ“]
		rot += 0.2f;
		//k¬
		if (a >= 0.0f) {
			a -= 0.02f;
			b -= 0.02f;
			
		}
		else {
			isDead = true;
		}
	}
}

void Key::Draw()
{
	//Œ®
	if (isDead==false) {
		DrawRotaGraph3(pos_.x - size_.x / 2, pos_.y - size_.y / 2, size_.x / 2, size_.y / 2, a, b,rot, textruehandle_, TRUE);
		//DrawRotaGraph2()
		//DrawFormatString(pos_.x - 15, pos_.y - 10, GetColor(0, 0, 0), "key");
	}
}

void Key::OnCollision(Object* objct)
{
	if (objct->GetObjectType() == ObjectType::PLAYER) {
		isCollision_ = false;
		isGet = true;
	}
}
