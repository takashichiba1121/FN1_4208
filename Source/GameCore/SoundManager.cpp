#include "SoundManager.h"
#include"Dxlib.h"

SoundManager* SoundManager::Instance()
{
	static SoundManager instance;

	return &instance;
}

uint32_t SoundManager::LoadSound(const std::string fileName)
{

	for (int32_t i = 0; i < soundNames.size(); i++)
	{
		if (fileName == soundNames[i])
		{
			return i;
		}
	}

	soundNames.push_back(fileName);

	return DxLib::LoadSoundMem(fileName.c_str());
}
void SoundManager::Finalize()
{
	soundNames.clear();

	InitSoundMem();
}

