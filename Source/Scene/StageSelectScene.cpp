#include "StageSelectScene.h"
#include "DxLib.h"
#include"Input.h"
#include"CollisionManager.h"
#include "StageManager.h"
#include "SceneManager.h"
#include <imgui.h>

void StageSelectScene::Initialize()
{
	stageFileName_ = { 
		"Error",
	};
}

void StageSelectScene::Update()
{
	if (Input::GetKeyTrigger(Input::Key::A) || Input::GetKeyTrigger(Input::Key::Left))
	{
		if (selectStageNum_ > 0)
		{
			selectStageNum_--;
		}
	}
	else if (Input::GetKeyTrigger(Input::Key::D) || Input::GetKeyTrigger(Input::Key::Right))
	{
		if (selectStageNum_ < stageFileName_.size() - 1)
		{
			selectStageNum_++;
		}
	}
	else if (Input::GetKeyTrigger(Input::Key::Space) || Input::GetKeyTrigger(Input::Key::Enter))
	{
		SceneManager::GetInstance()->ChangeScene("GAME");
		StageManager::GetInstance()->LoadStageObjectFile(stageFileName_[selectStageNum_]);
	}

#ifdef _DEBUG

	ImGui::Begin("selectNum");

	ImGui::Text("select: %d", selectStageNum_);

	ImGui::End();
#endif

}

void StageSelectScene::Draw()
{
	
}

void StageSelectScene::Finalize()
{
}
