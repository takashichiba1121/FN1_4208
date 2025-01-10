#include"Bubble.h"
#include"DxLib.h"
#include"CollisionManager.h"
#include"Random.h"

Bubble::~Bubble() {
	//CollisionManager::GetInstance()->RemoveObject(this);
}

void Bubble::Initialize(const Vector2 pos) {
	pos_ = pos;
	size = Random::RandomFloat(8.0f, 12.0f);
	size_ = { size,size };
	isExclude_ = false;

	objectType_ = ObjectType::NONE;
	CollisionManager::GetInstance()->AddObject(this);
}

void Bubble::Update(const float line) {

	oldPos_ = pos_;

	//�ړ��ʂ������_����
	pos_.x += Random::RandomFloat(-1.0f, 1.0f);
	pos_.y -= vector.y + Random::RandomFloat(-1.0f, 1.0f);

	//�����������ɍs���Ə���
	if (pos_.y < line) {
		isDead = true;
	}
	if (isDead)
	{
		CollisionManager::GetInstance()->RemoveObject(this);
	}
}

void Bubble::Draw() {

	DrawCircle((int)pos_.x, (int)pos_.y, (int)size, GetColor(255, 255, 255), false);
}

void Bubble::OnCollision(Object* objct) {

	//�u���b�N�ɓ�����Ə���
	if (objct->GetObjectType() == ObjectType::FLOAT_BLOCK ||
		objct->GetObjectType() == ObjectType::NOT_FLOAT_BLOCK) {
		isDead = true;
	}
}