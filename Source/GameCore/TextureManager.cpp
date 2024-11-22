#include "TextureManager.h"
#include"Dxlib.h"

TextureManager* TextureManager::Instance()
{
	static TextureManager instance;

	return &instance;
}

uint32_t TextureManager::LoadTexture(const std::string fileName)
{

	for (int32_t i = 0; i < textureNames_.size(); i++)
	{
		if (fileName == textureNames_[i].name)
		{
			return textureNames_[i].id;
		}
	}

	uint32_t id=DxLib::LoadGraph(fileName.c_str());

	textureNames_.push_back({ id,fileName });

	return id;
}
void TextureManager::Finalize()
{
	textureNames_.clear();

	InitGraph();
}

