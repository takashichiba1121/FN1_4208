#include "SceneManager.h"
#include<cassert>

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}

void SceneManager::ChangeScene(const std::string& sceneName, const std::string& sceneChangeName)
{
	assert(sceneFactory_);
	assert(sceneChangeFactory_);
	assert(nextScene_ == nullptr);

	nextScene_ = sceneFactory_->CreateScene(sceneName);

	SceneChange_ = sceneChangeFactory_->CreateSceneChange(sceneChangeName);
	SceneChange_->SetIsStart(true);
}

void SceneManager::Update()
{
	SceneChange_->Update();
	//次のシーンの予約があるなら
	if ( nextScene_ )
	{
		if (SceneChange_->GetIsClose())
		{
			//旧シーンの終了
			if (scene_)
			{
				scene_->Finalize();
				scene_.reset();
			}

			//シーン切り替え
			scene_ = std::move(nextScene_);

			//シーンマネージャーをセット
			scene_->SetSceneManager(this);

			//次のシーンを初期化する
			scene_->Initialize();
			SceneChange_->SetIsOpenStart(true);
		}
	}

	scene_->Update();
}

void SceneManager::Draw()
{
	scene_->Draw();
	SceneChange_->Draw();
}

void SceneManager::SetSceneFactory(AbstractSceneFactory* factory)
{
	sceneFactory_ = factory;
}

void SceneManager::SetSceneChangeFactory(ISceneChangeFactory* factory_)
{
	sceneChangeFactory_ = factory_;
}

void SceneManager::Finalize()
{
	if ( scene_ )
	{
		scene_->Finalize();
		scene_.reset();
	}
}