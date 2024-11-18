#include"BubbleEmitter.h"
#include"Inversion.h"

void BubbleEmitter::Initialize(const int timer) {
	maxTimer = timer;
}

void BubbleEmitter::Update(const Vector2 pos) {

	emitTimer--;

	if (emitTimer < 0) {

		if (!Inversion::GetInstance()->GetIsInversion()) {

			//�p�[�e�B�N������
			std::unique_ptr<Bubble>b = std::make_unique<Bubble>();
			b->Initialize(pos);
			bubble_.push_back(std::move(b));
		}

		//�^�C�}�[���Z�b�g
		emitTimer = maxTimer;
	}

	//�p�[�e�B�N���X�V
	for (std::unique_ptr<Bubble>& b : bubble_) {

		b->Update(horizontal);
	}
	//�f�X�t���O�̗������G���폜
	bubble_.remove_if([](std::unique_ptr<Bubble>& b) {
		return b->GetIsDead();
		});

}

void BubbleEmitter::Draw() {
	for (std::unique_ptr<Bubble>& b : bubble_) {
		b->Draw();
	}
}