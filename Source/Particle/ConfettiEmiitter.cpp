#include "ConfettiEmiitter.h"

void ConfettiEmiitter::Initialize(const int timer)
{
	maxTimer = timer;
}

void ConfettiEmiitter::Update()
{
	emitTimer--;

	if (emitTimer < 0) {

		//�p�[�e�B�N������
		std::unique_ptr<Confetti>c = std::make_unique<Confetti>();
		c->Initialize();
		confetti_.push_back(std::move(c));
		//�^�C�}�[���Z�b�g
		emitTimer = maxTimer;
	}

	//�p�[�e�B�N���X�V
	for (std::unique_ptr<Confetti>& b : confetti_) {

		b->Update();
	}
	//�f�X�t���O�̗������G���폜
	confetti_.remove_if([](std::unique_ptr<Confetti>& c) {
		return c->GetIsDead();
		});
}

void ConfettiEmiitter::Draw()
{
	for (std::unique_ptr<Confetti>& c : confetti_) {
		c->Draw();
	}
}
