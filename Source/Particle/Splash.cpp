#include"Splash.h"
#include"DxLib.h"
#include"Random.h"

void Splash::Initialize(const Vector2 pos, const float grv) {
	position = pos;
	size = MinSize + (abs(grv) / (MaxGravity / 2.5f));	//速度に合わせてサイズを変更
	vector = {
		Random::RandomFloat(-MaxVecX,MaxVecX),
		Random::RandomFloat(-abs(grv / 2.0f),-abs(grv / 4.0f)),
	};
}

void Splash::Update(const float line) {

	//水平線より下に行くと消滅
	if (position.y > line) {
		isDead = true;
	}

	vector.y += Accel;	//下方向に加速
	position += vector;
}

void Splash::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawCircle((int)position.x, (int)position.y, (int)size, GetColor(100, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}