#pragma once
#include"BaseScene.h"
#include"AbstractSceneFactory.h"
#include "ISceneChange.h"
#include "ISceneChangeFactory.h"

class SceneManager
{
private:

	std::unique_ptr<BaseScene> scene_;
	std::unique_ptr<BaseScene> nextScene_;
	AbstractSceneFactory* sceneFactory_ = nullptr;
	ISceneChangeFactory* sceneChangeFactory_ = nullptr;
	std::unique_ptr<ISceneChange> SceneChange_ = nullptr;

public:

	static SceneManager* GetInstance();

	void ChangeScene(const std::string& sceneName_, const std::string& sceneChangeName = "BASIC");

	void Update();

	void Draw();

	void SetSceneFactory(AbstractSceneFactory* factory_);

	void SetSceneChangeFactory(ISceneChangeFactory* factory_);

	void Finalize();


private:

	~SceneManager() = default;
	SceneManager() = default;

	//コピーコンストラクタ・代入演算子削除
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
};
