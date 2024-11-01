#pragma once
#include"Splash.h"
#include <memory>
#include <list>

class SplashEmitter {

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="timer">���Ԃ����c�鎞��</param>
	void Initialize(const int timer);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="size">�T�C�Y</param>
	/// <param name="grv">�����A�㏸���x</param>
	void Update(const Vector2 pos, const float size, const float grv);

	void Draw();

	void SetHorizontal(const float line) { horizontal = line; }

private:

	std::list<std::unique_ptr<Splash>> splash_;

	float horizontal = 0.0f;

	int maxTimer = 0;
	int emitTimer = 0;
};