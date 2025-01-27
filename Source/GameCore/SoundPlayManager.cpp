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

	bgm.titleScene = SoundManager::Instance()->LoadSound("Resources\\BGM\\titleBGM.mp3");
	bgm.gameScene = SoundManager::Instance()->LoadSound("Resources\\BGM\\gamePlayBGM.mp3");
}

void SoundPlayManager::SoundPlay(int sound, int volume) {

	ChangeVolumeSoundMem(volume, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_BACK, true);
}

void SoundPlayManager::BGMPlay(int bgm, int volume) {
	ChangeVolumeSoundMem(volume, bgm);
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, true);
}

void SoundPlayManager::BGMStop(int bgm) {
	StopSoundMem(bgm);
}

void SoundPlayManager::Finalize() {

	SoundManager::Instance()->Finalize();
}