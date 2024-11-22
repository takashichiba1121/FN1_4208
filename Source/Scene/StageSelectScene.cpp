#include "StageSelectScene.h"
#include "DxLib.h"
#include"Input.h"
#include"CollisionManager.h"
#include "StageManager.h"
#include "SceneManager.h"
#include <imgui.h>

void StageSelectScene::Initialize()
{
	StageManager::GetInstance()->Initialize();
	preview1_.Initialize();
	preview1_.pos_ = { 100,100 };
	preview1_.size_ = { 0.5f,0.5f };
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
		if (static_cast<size_t>(selectStageNum_) < StageManager::GetInstance()->GetSrageFileNameNum() - 1)
		{
			selectStageNum_++;
		}
	}
	else if (Input::GetKeyTrigger(Input::Key::Space) || Input::GetKeyTrigger(Input::Key::Enter))
	{
		SceneManager::GetInstance()->ChangeScene("GAME");
		StageManager::GetInstance()->SelectLevelNum(selectStageNum_);
	}

	preview1_.Update(StageManager::GetInstance()->GetStageFileName(selectStageNum_));

#ifdef _DEBUG

	ImGui::Begin("selectNum");

	ImGui::Text("select: %d", selectStageNum_);

	ImGui::End();
#endif

}

void StageSelectScene::Draw()
{
	preview1_.Draw();
}

void StageSelectScene::Finalize()
{
}
