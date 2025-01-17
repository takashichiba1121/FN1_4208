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

public:

	void LoadAllSound();

	void SoundPlay(int sound, int volume);

	void Finalize();
	
	const int Jump() { return jump; }
	const int Swim() { return swim; }
	const int Inversion() { return inversion; }

private:
	int jump;
	int swim;
	int inversion;
};
