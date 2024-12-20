#pragma once
#include<string>
#include<vector>

class TextureManager
{
#pragma region Singleton
private:
	TextureManager() {};

	~TextureManager() {};
public:
	TextureManager(const TextureManager& carManager) = delete;

	TextureManager& operator=(const TextureManager& carManager) = delete;

	static TextureManager* Instance();
#pragma endregion
public:
	struct Texture
	{
		uint32_t id;
		std::string name;
	};

public:
	/// <summary>
	/// テクスチャの読み込み
	/// </summary>
	/// <param name="fileName">テクスチャのパス</param>
	/// <returns>テクスチャの識別番号</returns>
	uint32_t LoadTexture(const std::string fileName = "NULL");

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

private:
	std::vector<Texture> textureNames_;
};



