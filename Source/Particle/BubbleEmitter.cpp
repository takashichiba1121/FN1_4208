#include"BubbleEmitter.h"
#include"Inversion.h"

void BubbleEmitter::Initialize(const int timer) {
	maxTimer = timer;
}

void BubbleEmitter::Update(const Vector2 pos) {

	emitTimer--;

	if (emitTimer < 0) {

		if (!Inversion::GetInstance()->GetIsInversion()) {

			//パーティクル生成
			std::unique_ptr<Bubble>b = std::make_unique<Bubble>();
			b->Initialize(pos);
			bubble_.push_back(std::move(b));
		}

		//タイマーリセット
		emitTimer = maxTimer;
	}

	//パーティクル更新
	for (std::unique_ptr<Bubble>& b : bubble_) {

		b->Update(horizontal);
	}
	//デスフラグの立った敵を削除
	bubble_.remove_if([](std::unique_ptr<Bubble>& b) {
		return b->GetIsDead();
		});

}

void BubbleEmitter::Draw() {
	for (std::unique_ptr<Bubble>& b : bubble_) {
		b->Draw();
	}
}