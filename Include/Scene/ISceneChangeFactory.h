#pragma once
#include "ISceneChange.h"
#include <string>
#include <memory>

class ISceneChangeFactory
{
public:
	virtual ~ISceneChangeFactory() = default;

	//�V�[������
	virtual std::unique_ptr<ISceneChange> CreateSceneChange(const std::string& sceneChangeName) = 0;

private:

};