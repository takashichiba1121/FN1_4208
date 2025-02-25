#include "Key.h"
#include "Input.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "StageManager.h"
#include "SoundPlayManager.h"


void Key::Initialize()
{
	
	objectType_ = ObjectType::KEY;
	isExclude_ = false;
	CollisionManager::GetInstance()->AddObject(this);

	//�摜�ǂݍ���
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\Key_1.png");

	isLock = true;
	isKey = true;
}

void Key::Update()
{	
	ObjectUpdate();
	//���������
	if (isGet) {
		isDead = true;
		////��]
		//rot += 0.2f;
		////�k��
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
	//��
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
			SoundPlayManager::Instance()->SoundPlay(SoundPlayManager::Instance()->GetSound().key, 255 * 0.5f);
		}
		isGet = true;
		isLock = false;
		isKey = false;
		
	}
}
