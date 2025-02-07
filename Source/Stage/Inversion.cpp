#include"Inversion.h"
#include"Input.h"
#include"StageManager.h"
#include"Water.h"
#include"StageManager.h"
#include"SoundPlayManager.h"

void Inversion::Initialize() {
	isFront = true;
	isReverse = false;
}

void Inversion::Update() {

	endInversion = false;

	////キー操作で反転
	//if (!Water::GetInstance()->GetIsChangeHorizontal() && !StageManager::GetInstance()->GetIsClear()) {
	//	if (Input::GetKeyTrigger(Input::Key::Q)) {
	//		isInversion = true;
	//	}
	//}

	//反転中の処理
	if (isInversion) {

		if (frame == 15) {
			SoundPlayManager::Instance()->SoundPlay(SoundPlayManager::Instance()->GetSound().inversionB);
		}

		if (frame == MaxFrame / 2) {
			isReverse = !isReverse;
		}

		frame++;	//フレームを進める
		//水平線のイージング
		horizontalPos = easeStartPos + Easing(frame / MaxFrame) * (easeEndPos - easeStartPos);
		Water::GetInstance()->SetHorizontal(horizontalPos);
		StageManager::GetInstance()->Inversion(Easing(frame / MaxFrame));
		
		//イージング終了後の処理
		if (frame >= MaxFrame) {
			isInversion = false;
			endInversion = true;
			frame = 0.0f;
			isFront = !isFront;
			horizontalPos = Water::GetInstance()->GetHorizontal();

  			ResetEasing();
		}
	}
	else {
		ResetEasing();
	}

	//水の反転処理
	Water::GetInstance()->Inversion(Easing(frame / MaxFrame), isFront);

}

void Inversion::ResetEasing() {
	//イージング初期地点を設定
	easeStartPos = Water::GetInstance()->GetHorizontal();
	//イージング終了地点を設定
	easeEndPos = WIN_HEIGHT / 2 + (WIN_HEIGHT / 2 - Water::GetInstance()->GetHorizontal());

	StageManager::GetInstance()->SetTentPos();
}

Inversion* Inversion::GetInstance()
{
	static Inversion instance;
	return &instance;
}