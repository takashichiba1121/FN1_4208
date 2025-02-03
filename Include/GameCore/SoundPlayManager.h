#pragma once
#include "SoundManager.h"
#include<string>
#include<vector>

class SoundPlayManager
{
#pragma region Singleton
private:
	SoundPlayManager() {};

	~SoundPlayManager() {};
public:
	SoundPlayManager(const SoundPlayManager& carManager) = delete;

	SoundPlayManager& operator=(const SoundPlayManager& carManager) = delete;

	static SoundPlayManager* Instance();
#pragma endregion

private:

	struct Sounds {
		int jump;
		int swim;
		int inversionA;
		int inversionB;
		int waterA;
		int waterB;
		int key;
		int clear;
		int select;
		int gameover;
		int block_break;
	};

	struct BGM {
		int titleScene;
		int gameScene;
	};

public:

	void LoadAllSound();

	void SoundPlay(int sound, int volume = 150);

	void BGMPlay(int bgm, int volume = 150);
	void BGMStop(int bgm);

	void Finalize();
	
	const Sounds GetSound() { return sounds; }
	const BGM GetBGM() { return bgm; }
	
private:

	Sounds sounds;
	BGM bgm;
};
