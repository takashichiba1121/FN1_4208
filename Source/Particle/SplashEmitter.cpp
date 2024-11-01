#include"SplashEmitter.h"

void SplashEmitter::Initialize(const int timer) {
	maxTimer = timer;
}

void SplashEmitter::Update(const Vector2 pos, const float size, const float grv) {

	//水平線に触れているときにでるしぶき
	if (pos.y + size >= horizontal && pos.y - size <= horizontal) {
		//パーティクル生成
		for (int i = 0; i < (int)abs(grv) / 4; i++) {
			std::unique_ptr<Splash>splash = std::make_unique<Splash>();
			splash->Initialize({ pos.x, horizontal }, grv);
			splash_.push_back(std::move(splash));
		}
	}

	//水平線から出た後自機から出続けるしぶき
	if (horizontal > pos.y) {

		emitTimer--;

		if (emitTimer >= 0) {
			//パーティクル生成
			std::unique_ptr<Splash>splash = std::make_unique<Splash>();
			splash->Initialize(pos, 0.5f);
			splash_.push_back(std::move(splash));
		}
		
	}
	else {
		//タイマーリセット
		emitTimer = maxTimer;
	}

	//パーティクル更新
	for (std::unique_ptr<Splash>& splash : splash_) {
		splash->Update(horizontal);
	}
	//デスフラグ立ったら削除
	splash_.remove_if([](std::unique_ptr<Splash>& splash) {
		return splash->GetIsDead();
		});

}

void SplashEmitter::Draw() {
	for (std::unique_ptr<Splash>& splash : splash_) {
		splash->Draw();
	}
}