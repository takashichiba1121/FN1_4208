#pragma once
#include "ISceneChangeFactory.h"

class SceneChangeFactory :public ISceneChangeFactory
{
public:
	SceneChangeFactory();
	~SceneChangeFactory();

	static SceneChangeFactory* GetInstance();

	/// <summary>
	/// �V�[������
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	/// <returns>���������V�[��</returns>
	std::unique_ptr<ISceneChange> CreateSceneChange(const std::string& sceneChangeName)override;

private:

};