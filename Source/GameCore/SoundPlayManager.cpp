#include "SoundPlayManager.h"
#include"Dxlib.h"

SoundPlayManager* SoundPlayManager::Instance()
{
	static SoundPlayManager instance;

	return &instance;
}

void SoundPlayManager::LoadAllSound() {
	jump = SoundManager::Instance()->LoadSound("Resources\\Sound\\jump.wav");
	swim = SoundManager::Instance()->LoadSound("Resources\\Sound\\swim.wav");
}

void SoundPlayManager::SoundPlay(int sound, int volume) {

	ChangeVolumeSoundMem(volume, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_BACK, true);
}

void SoundPlayManager::Finalize() {

	SoundManager::Instance()->Finalize();
}