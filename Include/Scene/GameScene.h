#pragma once
#include "BaseScene.h"
#include "Player.h"
#include <memory>

class GameScene :
    public BaseScene
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:

	std::unique_ptr<Object> player;

};

