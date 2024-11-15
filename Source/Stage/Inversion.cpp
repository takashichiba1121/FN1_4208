#include"Inversion.h"
#include"Input.h"
#include"StageManager.h"
#include"Water.h"

void Inversion::Update() {

	//キー操作で反転
	if (Input::GetKeyTrigger(Input::Key::Q)) {
		isInversion = true;
	}

	//反転中の処理
	if (isInversion) {

		frame++;	//フレームを進める
		//水平線のイージング
		horizontalPos = easeStartPos + Easing(frame / MaxFrame) * (easeEndPos - easeStartPos);
		Water::GetInstance()->SetHorizontal(horizontalPos);
		StageManager::GetInstance()->Inversion(Easing(frame / MaxFrame));
		
		//イージング終了後の処理
		if (frame >= MaxFrame) {
			isInversion = false;
			frame = 0.0f;
			isFront = !isFront;
			horizontalPos = Water::GetInstance()->GetHorizontal();
		}
	}
	else {
	
		//イージング初期地点を設定
		easeStartPos = Water::GetInstance()->GetHorizontal();
		//イージング終了地点を設定
		easeEndPos = WIN_HEIGHT / 2 + (WIN_HEIGHT / 2 - Water::GetInstance()->GetHorizontal());

		StageManager::GetInstance()->SetTentPos();
	}

	//水の反転処理
	Water::GetInstance()->Inversion(Easing(frame / MaxFrame), isFront);

}

Inversion* Inversion::GetInstance()
{
	static Inversion instance;
	return &instance;
}