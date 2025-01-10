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

	//‰æ‘œ“Ç‚Ýž‚Ý
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Key.png");

	isLock = true;
	isKey = true;
}

void Key::Update()
{	
	ObjectUpdate();
	//Œ®Žæ‚Á‚½‚ç
	if (isGet) {
		isDead = true;
		////‰ñ“]
		//rot += 0.2f;
		////k¬
		//if (s >= 0.0f) {
		//	s -= 0.02f;
		//}
		//else {
		//	isDead = true;
		//}
	}
}

void Key::Draw()
{
	//Œ®
	if (isDead==false) {
		//DrawRotaGraph3F(pos_.x, pos_.y, size_.x / 2, size_.y / 2, s, s,rot, textruehandle_, TRUE);
		DrawRotaGraph3F(
			pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, 0.0f, 0.0f,
			(double)(size_.x / 64.0), (double)(size_.y / 64.0), 0, textruehandle_, true);
	}
}

void Key::OnCollision(Object* objct)
{
	if (objct->GetObjectType() == ObjectType::PLAYER) {
		if (isGet == false) {
			StageManager::GetInstance()->GetKey();
		}
		isGet = true;
		isLock = false;
		isKey = false;
		
	}
}
