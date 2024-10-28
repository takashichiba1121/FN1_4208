#include"SplashEmitter.h"

void SplashEmitter::Initialize(const int timer) {
	maxTimer = timer;
}

void SplashEmitter::Update(const Vector2 pos) {


	if (horizontal >= pos.y) {

		emitTimer--;

		if (emitTimer >= 0) {

			//�p�[�e�B�N������
			std::unique_ptr<Splash>splash = std::make_unique<Splash>();
			splash->Initialize(pos);
			splash_.push_back(std::move(splash));
		}
		
	}
	else {
		//�^�C�}�[���Z�b�g
		emitTimer = maxTimer;
	}

	//�p�[�e�B�N���X�V
	for (std::unique_ptr<Splash>& splash : splash_) {

		splash->Update(horizontal);
	}
	//�f�X�t���O�̗������G���폜
	splash_.remove_if([](std::unique_ptr<Splash>& splash) {
		return splash->GetIsDead();
		});

}

void SplashEmitter::Draw() {
	for (std::unique_ptr<Splash>& splash : splash_) {
		splash->Draw();
	}
}