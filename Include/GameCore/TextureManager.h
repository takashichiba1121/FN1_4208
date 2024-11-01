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
	/// <summary>
	/// �e�N�X�`���̓ǂݍ���
	/// </summary>
	/// <param name="fileName">�e�N�X�`���̃p�X</param>
	/// <returns>�e�N�X�`���̎��ʔԍ�</returns>
	uint32_t LoadTexture(const std::string fileName = "NULL");

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private:
	std::vector<std::string> textureName;
	uint32_t srvIncrementIndex = 0;
};



