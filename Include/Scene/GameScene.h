#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "Block.h"
#include "LevitationBlock.h"
#include <memory>

class GameScene :
    public BaseScene
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:

	Object* player = nullptr;

	std::unique_ptr<Block> block;
	std::unique_ptr<LevitationBlock> floatBlock;
	std::unique_ptr<Object> player;

};

