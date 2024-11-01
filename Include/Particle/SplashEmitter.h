#pragma once
#include"Splash.h"
#include <memory>
#include <list>

class SplashEmitter {

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="timer">しぶきが残る時間</param>
	void Initialize(const int timer);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="size">サイズ</param>
	/// <param name="grv">落下、上昇速度</param>
	void Update(const Vector2 pos, const float size, const float grv);

	void Draw();

	void SetHorizontal(const float line) { horizontal = line; }

private:

	std::list<std::unique_ptr<Splash>> splash_;

	float horizontal = 0.0f;

	int maxTimer = 0;
	int emitTimer = 0;
};