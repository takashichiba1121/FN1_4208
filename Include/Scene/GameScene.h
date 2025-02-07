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
#include"SoundPlayManager.h"
#include"Pause.h"

class GameScene :
    public BaseScene
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	float Easing(const float x) { return x < 0.5 ? 16 * x * x * x * x * x : 1 - (float)pow(-2 * x + 2, 5) / 2; }

	std::unique_ptr<Block> block;
	std::unique_ptr<LevitationBlock> floatBlock;
	std::unique_ptr<BreakBlock> breakBlock;
	std::unique_ptr<Player> player;
	std::unique_ptr<Goal> goal;
	std::unique_ptr<Key> key;
	std::unique_ptr<SpongeBlock> spongeBlock;

	std::unique_ptr<Drain> drain;

	std::unique_ptr<TutorialObject> tutorial;

	std::unique_ptr<Pause> pause_;

	EditStage test;

	SoundPlayManager* soundPlayManager;

	int32_t backGroundTextruehandle_ = 0;

	bool isPause=false;
};

