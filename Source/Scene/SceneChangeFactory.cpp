#include "SceneChangeFactory.h"
#include "BasicSceneChange.h"
#include "NoneSceneChange.h"

SceneChangeFactory::SceneChangeFactory()
{
}

SceneChangeFactory::~SceneChangeFactory()
{
}

SceneChangeFactory* SceneChangeFactory::GetInstance()
{
	static SceneChangeFactory lInstance;
	return &lInstance;
}

std::unique_ptr<ISceneChange> SceneChangeFactory::CreateSceneChange(const std::string& sceneChangeName)
{

	std::unique_ptr<ISceneChange> newSceneChange = nullptr;

	if (sceneChangeName == "BASIC")
	{
		newSceneChange = std::make_unique<BasicSceneChange>();
		newSceneChange->Initialize();
	}

	if (sceneChangeName == "NONE")
	{
		newSceneChange = std::make_unique<NoneSceneChange>();
		newSceneChange->Initialize();
	}

	return std::move(newSceneChange);

}