#pragma once
#include<string>
#include<vector>

class SoundManager
{
#pragma region Singleton
private:
	SoundManager() {};

	~SoundManager() {};
public:
	SoundManager(const SoundManager& carManager) = delete;

	SoundManager& operator=(const SoundManager& carManager) = delete;

	static SoundManager* Instance();
#pragma endregion
public:
	/// <summary>
	/// テクスチャの読み込み
	/// </summary>
	/// <param name="fileName">テクスチャのパス</param>
	/// <returns>テクスチャの識別番号</returns>
	uint32_t LoadSound(const std::string fileName = "NULL");

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

private:
	std::vector<std::string> soundNames;
	uint32_t srvIncrementIndex = 0;
};



