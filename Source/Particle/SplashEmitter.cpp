#include"SplashEmitter.h"

void SplashEmitter::Initialize(const int timer) {
	maxTimer = timer;
}

void SplashEmitter::Update(const Vector2 pos) {


	if (horizontal >= pos.y) {

		emitTimer--;

		if (emitTimer >= 0) {

			//パーティクル生成
			std::unique_ptr<Splash>splash = std::make_unique<Splash>();
			splash->Initialize(pos);
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
	//デスフラグの立った敵を削除
	splash_.remove_if([](std::unique_ptr<Splash>& splash) {
		return splash->GetIsDead();
		});

}

void SplashEmitter::Draw() {
	for (std::unique_ptr<Splash>& splash : splash_) {
		splash->Draw();
	}
}