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
	/// �e�N�X�`���̓ǂݍ���
	/// </summary>
	/// <param name="fileName">�e�N�X�`���̃p�X</param>
	/// <returns>�e�N�X�`���̎��ʔԍ�</returns>
	uint32_t LoadSound(const std::string fileName = "NULL");

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private:
	std::vector<std::string> soundNames;
	uint32_t srvIncrementIndex = 0;
};



