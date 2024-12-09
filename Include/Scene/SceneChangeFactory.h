#pragma once
#include "ISceneChangeFactory.h"

class SceneChangeFactory :public ISceneChangeFactory
{
public:
	SceneChangeFactory();
	~SceneChangeFactory();

	static SceneChangeFactory* GetInstance();

	/// <summary>
	/// シーン生成
	/// </summary>
	/// <param name="sceneName">シーン名</param>
	/// <returns>生成したシーン</returns>
	std::unique_ptr<ISceneChange> CreateSceneChange(const std::string& sceneChangeName)override;

private:

};