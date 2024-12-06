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
#include"Drain.h"
#include"TutorialObject.h"

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
	std::unique_ptr<Player> player;
	std::unique_ptr<Goal> goal;
	std::unique_ptr<Key> key;
	std::unique_ptr<SpongeBlock> spongeBlock;

	std::unique_ptr<Drain> drain;

	std::unique_ptr<TutorialObject> tutorial;

	EditStage test;

};

