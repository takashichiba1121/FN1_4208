#include"Splash.h"
#include"DxLib.h"
#include"Random.h"

void Splash::Initialize(const Vector2 pos, const float grv) {
	position = pos;
	size = MinSize + (abs(grv) / (MaxGravity / 2.5f));	//���x�ɍ��킹�ăT�C�Y��ύX
	vector = {
		Random::RandomFloat(-MaxVecX,MaxVecX),
		Random::RandomFloat(-abs(grv / 2.0f),-abs(grv / 4.0f)),
	};
}

void Splash::Update(const float line) {

	//��������艺�ɍs���Ə���
	if (position.y > line) {
		isDead = true;
	}

	vector.y += Accel;	//�������ɉ���
	position += vector;
}

void Splash::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawCircle((int)position.x, (int)position.y, (int)size, GetColor(100, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}