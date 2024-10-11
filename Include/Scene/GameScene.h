#pragma once
#include "BaseScene.h"
#include "Player.h"

class GameScene :
    public BaseScene
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:

	Player* player = nullptr;;
};

