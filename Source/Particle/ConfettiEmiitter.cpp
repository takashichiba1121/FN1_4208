#include "ConfettiEmiitter.h"

void ConfettiEmiitter::Initialize(const int timer)
{
	maxTimer = timer;
}

void ConfettiEmiitter::Update()
{
	emitTimer--;

	if (emitTimer < 0) {

		//パーティクル生成
		std::unique_ptr<Confetti>c = std::make_unique<Confetti>();
		c->Initialize();
		confetti_.push_back(std::move(c));
		//タイマーリセット
		emitTimer = maxTimer;
	}

	//パーティクル更新
	for (std::unique_ptr<Confetti>& b : confetti_) {

		b->Update();
	}
	//デスフラグの立った敵を削除
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
