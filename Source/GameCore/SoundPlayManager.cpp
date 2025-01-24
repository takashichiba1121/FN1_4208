#include "SoundPlayManager.h"
#include"Dxlib.h"

SoundPlayManager* SoundPlayManager::Instance()
{
	static SoundPlayManager instance;

	return &instance;
}

void SoundPlayManager::LoadAllSound() {
	sounds.jump = SoundManager::Instance()->LoadSound("Resources\\Sound\\jump.wav");
	sounds.swim = SoundManager::Instance()->LoadSound("Resources\\Sound\\swim.wav");
	sounds.inversionA = SoundManager::Instance()->LoadSound("Resources\\Sound\\inversionA.wav");
	sounds.inversionB = SoundManager::Instance()->LoadSound("Resources\\Sound\\inversionB.wav");
	sounds.waterA = SoundManager::Instance()->LoadSound("Resources\\Sound\\waterA.wav");
	sounds.waterB = SoundManager::Instance()->LoadSound("Resources\\Sound\\waterB.wav");
	sounds.key = SoundManager::Instance()->LoadSound("Resources\\Sound\\key.wav");
	sounds.clear = SoundManager::Instance()->LoadSound("Resources\\Sound\\clear.wav");
	sounds.select = SoundManager::Instance()->LoadSound("Resources\\Sound\\select.wav");
	sounds.gameover = SoundManager::Instance()->LoadSound("Resources\\Sound\\gameover.wav");
}

void SoundPlayManager::SoundPlay(int sound, int volume) {

	ChangeVolumeSoundMem(volume, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_BACK, true);
}

void SoundPlayManager::Finalize() {

	SoundManager::Instance()->Finalize();
}