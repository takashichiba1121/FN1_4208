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

	previews_.resize(StageManager::GetInstance()->GetStageFileNameNum());

	int32_t itemCount = 0;

	for (auto& item : previews_)
	{
		item.Initialize(StageManager::GetInstance()->GetStageFileName(itemCount));
		item.pos_ = { (float)WIN_WIDTH * 0.5f + (float)(itemCount * (float)((WIN_WIDTH * 0.5) + 100)),(float)WIN_HEIGHT * 0.5f };
		item.size_ = { 0.5f,0.5f};
		itemCount++;
	}

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
		if (static_cast<size_t>(selectStageNum_) < StageManager::GetInstance()->GetStageFileNameNum() - 1)
		{
			selectStageNum_++;
		}
	}
	else if (Input::GetKeyTrigger(Input::Key::Space) || Input::GetKeyTrigger(Input::Key::Enter))
	{
		SceneManager::GetInstance()->ChangeScene("GAME");
		StageManager::GetInstance()->SelectLevelNum(selectStageNum_);
	}

	if (selectStageNum_ != selectStageOldNum_)
	{
		int32_t itemCount = 0;
		for (auto& item : previews_)
		{

			float defPosX = (float)WIN_WIDTH * 0.5f + (float)(itemCount * (float)((WIN_WIDTH * 0.5) + 100));

			item.pos_ = easeInQuad({ defPosX - (float)(selectStageOldNum_ * (float)((WIN_WIDTH * 0.5) + 100)) ,item.pos_.y }, { defPosX - (float)(selectStageNum_ * (float)((WIN_WIDTH * 0.5) + 100)) ,item.pos_.y },moveTime_/movemaxTime_);



			itemCount++;

		}

		if (moveTime_ > movemaxTime_)
		{
			selectStageOldNum_ = selectStageNum_;
			moveTime_ = 0;
		}
		else
		{
			moveTime_++;
		}

	}
	else
	{
		int32_t itemCount = 0;
		for (auto& item : previews_)
		{

			float defPosX = (float)WIN_WIDTH * 0.5f + (float)(itemCount * (float)((WIN_WIDTH * 0.5) + 100));

			item.pos_ = { defPosX - (float)(selectStageNum_ * (float)((WIN_WIDTH * 0.5) + 100)) ,item.pos_.y };

			itemCount++;

		}

		moveTime_ = 0;
	}

	/*int32_t itemCount = 0;
	for (auto& item : previews_)
	{
		
		float defPosX = (float)WIN_WIDTH * 0.5f + (float)(itemCount * (float)((WIN_WIDTH * 0.5) + 100));

		item.pos_ = { defPosX - (float)(selectStageNum_ * (float)((WIN_WIDTH * 0.5) + 100)) ,item.pos_.y };

		

		itemCount++;
		
	}*/


#ifdef _DEBUG

	ImGui::Begin("selectNum");

	ImGui::Text("select: %d", selectStageNum_);

	ImGui::End();
#endif

}

void StageSelectScene::Draw()
{
	for (auto item : previews_)
	{
		item.Draw();
	}
}

void StageSelectScene::Finalize()
{
}


Vector2 StageSelectScene::easeInQuad(Vector2 start, Vector2 end, float time)
{
	return start + time * time * (end - start);
}