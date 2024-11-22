#pragma once
#include"Confetti.h"
#include <memory>
#include <list>
class ConfettiEmiitter
{
public:

	void Initialize(const int timer);

	void Update();

	void Draw();

private:

	std::list<std::unique_ptr<Confetti>> confetti_;

	int maxTimer = 0;
	int emitTimer = 30;
};

