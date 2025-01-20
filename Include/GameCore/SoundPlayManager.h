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

	struct Sounds
	{
		int jump;
		int swim;
		int inversionA;
		int inversionB;
		int waterA;
		int waterB;
		int key;
		int clear;
	};

public:

	void LoadAllSound();

	void SoundPlay(int sound, int volume);

	void Finalize();
	
	const Sounds GetSound() { return sounds; }
	
private:

	Sounds sounds;
};
