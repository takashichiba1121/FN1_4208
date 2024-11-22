#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "Goal.h"
#include "Block.h"
#include "LevitationBlock.h"
#include "BreakBlock.h"
#include <memory>
#include "EditStage.h"
#include"Water.h"
#include"Inversion.h"
#include"Key.h"
#include"SpongeBlock.h"

class GameScene :
    public BaseScene
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:

	std::unique_ptr<Block> block;
	std::unique_ptr<LevitationBlock> floatBlock;
	std::unique_ptr<BreakBlock> breakBlock;
	std::unique_ptr<Object> player;
	std::unique_ptr<Goal> goal;
	std::unique_ptr<Key> key;
	std::unique_ptr<SpongeBlock> spongeBlock;

	EditStage test;

};

