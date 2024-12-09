#include"SplashEmitter.h"
#include"Random.h"
#include"Inversion.h"
#include"Water.h"

void SplashEmitter::Initialize(const int timer) {
	maxTimer = timer;
}

void SplashEmitter::Update(const Vector2 pos, const float size, const float grv) {

	horizontal = Water::GetInstance()->GetHorizontal();

	Vector2 pos_ = {
		Random::RandomFloat(pos.x - size, pos.x + size),
		Random::RandomFloat(pos.y - size, pos.y + size),
	};

	if (!Inversion::GetInstance()->GetIsInversion()) {

		//�������ɐG��Ă���Ƃ��ɂł邵�Ԃ�
		if (pos.y + size >= horizontal && pos.y - size <= horizontal) {
			//�p�[�e�B�N������
			for (int i = 0; i < (int)abs(grv) / 4; i++) {
				std::unique_ptr<Splash>splash = std::make_unique<Splash>();
				splash->Initialize({ pos_.x, horizontal }, grv);
				splash_.push_back(std::move(splash));
			}
		}

		//����������o���㎩�@����o�����邵�Ԃ�
		if (horizontal > pos.y) {

			emitTimer--;

			if (emitTimer >= 0) {
				//�p�[�e�B�N������
				std::unique_ptr<Splash>splash = std::make_unique<Splash>();
				splash->Initialize(pos_, 0.5f);
				splash_.push_back(std::move(splash));
			}

		}
		else {
			//�^�C�}�[���Z�b�g
			emitTimer = maxTimer;
		}
	}

	//�p�[�e�B�N���X�V
	for (std::unique_ptr<Splash>& splash : splash_) {
		splash->Update(horizontal);
	}
	//�f�X�t���O��������폜
	splash_.remove_if([](std::unique_ptr<Splash>& splash) {
		return splash->GetIsDead();
		});

}

void SplashEmitter::Draw() {
	for (std::unique_ptr<Splash>& splash : splash_) {
		splash->Draw();
	}
}