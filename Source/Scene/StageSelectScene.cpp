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

	SetFontSize(50);

}

void StageSelectScene::Update()
{
	if (!isNext_)
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

			isNext_ = true;

			int32_t itemCount = 0;
			for (auto& item : previews_)
			{
				if (selectStageNum_ != itemCount)
				{
					itemCount++;
					continue;
				}

				nextPreview_ = item;
				break;
			}
			
		}
	}
	else
	{
		
		nextPreview_.size_ = easeInQuad({ 0.5f,0.5f }, { 1.0f,1.0f }, moveNextTime_ / moveNextmaxTime_);

		if (moveNextTime_ > moveNextmaxTime_)
		{
			SceneManager::GetInstance()->ChangeScene("GAME");
			StageManager::GetInstance()->SelectLevelNum(selectStageNum_);
			moveNextTime_ = 0;
		}
		else
		{
			moveNextTime_++;
		}
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

	ImGui::Text("select: %d");

	ImGui::End();
#endif

}

void StageSelectScene::Draw()
{
	int32_t itemCount = 0;
	for (auto item : previews_)
	{
		item.Draw();
		
		DrawFormatString2F(item.pos_.x- (float)GetDrawStringWidth(std::string("ステージ"+itemCount).c_str(), std::string("ステージ" + itemCount).size()) / 2, (item.pos_.y - WIN_HEIGHT / 2 * item.size_.y) - 120, 0xffffff, 0xff0000, "ステージ%d", itemCount);
		DrawFormatString2F(item.pos_.x-(float)GetDrawStringWidth(item.levelName_.c_str(), item.levelName_.size())/2, (item.pos_.y - WIN_HEIGHT / 2 * item.size_.y) - 50, 0xffffff, 0xff0000, item.levelName_.c_str());
		itemCount++;
	}

	//仮置き
	DrawFormatString2F(0, 0, 0xffffff, 0xff0000, "移動:A D\n選択:SPACE");

	if (isNext_)
	{
		nextPreview_.Draw();
	}
}

void StageSelectScene::Finalize()
{
}


Vector2 StageSelectScene::easeInQuad(Vector2 start, Vector2 end, float time)
{
	return start + time * time * (end - start);
}