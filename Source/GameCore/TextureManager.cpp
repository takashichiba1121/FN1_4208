#include "TextureManager.h"
#include"Dxlib.h"

TextureManager* TextureManager::Instance()
{
	static TextureManager instance;

	return &instance;
}

uint32_t TextureManager::LoadTexture(const std::string fileName)
{

	for (int32_t i = 0; i < textureName.size(); i++)
	{
		if (fileName == textureName[i])
		{
			return i;
		}
	}

	textureName.push_back(fileName);

	return DxLib::LoadGraph(fileName.c_str());
}
void TextureManager::Finalize()
{
	textureName.clear();

	InitGraph();
}

