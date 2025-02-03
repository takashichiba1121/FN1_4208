#include "StageSelectScene.h"
#include "DxLib.h"
#include"Input.h"
#include"CollisionManager.h"
#include "StageManager.h"
#include "SceneManager.h"
#include <imgui.h>
#include "TextureManager.h"

void StageSelectScene::Initialize()
{
	soundPlayManager = SoundPlayManager::Instance();

	previews_.resize(StageManager::GetInstance()->GetStageFileNameNum());

	int32_t itemCount = 0;

	titleTextPos_ = { (float)WIN_WIDTH * 0.5f + (float)(-1 * (float)((WIN_WIDTH * 0.5) + 100)),(float)WIN_HEIGHT * 0.5f };

	for (auto& item : previews_)
	{
		item.Initialize(StageManager::GetInstance()->GetStageFileName(itemCount));
		item.pos_ = { (float)WIN_WIDTH * 0.5f + (float)(itemCount * (float)((WIN_WIDTH * 0.5) + 100)),(float)WIN_HEIGHT * 0.5f };
		item.size_ = { 0.5f,0.5f};
		itemCount++;
	}

	if (!CheckSoundMem(soundPlayManager->GetBGM().titleScene)) {
		soundPlayManager->BGMStop(soundPlayManager->GetBGM().gameScene);
		soundPlayManager->BGMPlay(soundPlayManager->GetBGM().titleScene);
	}

	SetFontSize(50);

	titleTextruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\TitleImage.png");

}

void StageSelectScene::Update()
{
	if (!isNext_)
	{
		if (!Input::GetIsUsePad())
		{
			if (Input::GetKeyTrigger(Input::Key::A) || Input::GetKeyTrigger(Input::Key::Left))
			{
				if (selectStageNum_ > -1)
				{
					selectStageOldNum_ = selectStageNum_;
					moveTime_ = 0;
					selectStageNum_--;
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().select);
				}
			}
			else if (Input::GetKeyTrigger(Input::Key::D) || Input::GetKeyTrigger(Input::Key::Right))
			{
				if (selectStageNum_ < StageManager::GetInstance()->GetStageFileNameNum() - 1)
				{
					selectStageOldNum_ = selectStageNum_;
					moveTime_ = 0;
					selectStageNum_++;
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().select);
				}
			}
			else if ((Input::GetKeyTrigger(Input::Key::Space) || Input::GetKeyTrigger(Input::Key::Enter)) &&selectStageNum_ == selectStageOldNum_)
			{
				if (selectStageNum_ == -1)
				{
					moveTime_ = movemaxTime_;
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA);
					isNext_ = true;
					isTitleExit_ = true;
				}
				else
				{
					moveTime_ = movemaxTime_;
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA);

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
		}
		else
		{
			if (Input::PadX() < -200)
			{
				if (selectStageNum_ > -1 && padMoveWait_==0)
				{
					selectStageOldNum_ = selectStageNum_;
					moveTime_ = 0;
					selectStageNum_--;
					padMoveWait_ = padMoveMaxWait_;
				}
			}
			else if (Input::PadX() > 200 && padMoveWait_ == 0)
			{
				if (selectStageNum_ < StageManager::GetInstance()->GetStageFileNameNum() - 1)
				{
					selectStageOldNum_ = selectStageNum_;
					moveTime_ = 0;
					selectStageNum_++;
					padMoveWait_ = padMoveMaxWait_;
				}
			}
			else if (Input::TriggerPadKey(PAD_INPUT_1) && selectStageNum_ == selectStageOldNum_)
			{
				if (selectStageNum_ == -1)
				{
					moveTime_ = movemaxTime_;
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA);
					isNext_ = true;
					isTitleExit_ = true;
				}
				else
				{
					moveTime_ = movemaxTime_;
					soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA);

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

			if (padMoveWait_ > 0)
			{
				padMoveWait_--;
			}
		}
	}
	else
	{
		if (!isTitleExit_)
		{
			nextPreview_.size_ = easeInQuad({ 0.5f,0.5f }, { 1.0f,1.0f }, moveNextTime_ / moveNextmaxTime_);

			if (moveNextTime_ > moveNextmaxTime_)
			{
				SceneManager::GetInstance()->ChangeScene("GAME", "LoadLevelName");
				StageManager::GetInstance()->SelectLevelNum(selectStageNum_);
				moveNextTime_ = 0;

			}
			else
			{
				moveNextTime_++;
			}
		}
		else
		{
			titleTextSize_ = easeInQuad({ 0.5f,0.5f }, { 1.0f,1.0f }, moveNextTime_ / moveNextmaxTime_);

			if (moveNextTime_ > moveNextmaxTime_)
			{
				SceneManager::GetInstance()->ChangeScene("TITLE");
				moveNextTime_ = 0;

			}
			else
			{
				moveNextTime_++;
			}
		}
	}


	if (selectStageNum_ != selectStageOldNum_)
	{


		float defTitlePosX = { (float)WIN_WIDTH * 0.5f + (float)(-1 * (float)((WIN_WIDTH * 0.5) + 100))};
		titleTextPos_ = easeInQuad({ defTitlePosX - (float)(selectStageOldNum_ * (float)((WIN_WIDTH * 0.5) + 100)) ,titleTextPos_.y }, { defTitlePosX - (float)(selectStageNum_ * (float)((WIN_WIDTH * 0.5) + 100)) ,titleTextPos_.y }, moveTime_ / movemaxTime_);

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
		float defTitlePosX = { (float)WIN_WIDTH * 0.5f + (float)(-1 * (float)((WIN_WIDTH * 0.5) + 100)) };
		titleTextPos_.x = defTitlePosX - (float)(selectStageNum_ * (float)((WIN_WIDTH * 0.5) + 100));
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
	int32_t itemCount = 1;

	for (auto item : previews_)
	{
		item.Draw();
		
		DrawFormatString2F(item.pos_.x- (float)GetDrawFormatStringWidth(std::string("ステージ"+ std::to_string(itemCount)).c_str()) / 2, (item.pos_.y - WIN_HEIGHT / 2 * item.size_.y) - 120, 0xffffff, 0xff0000, "ステージ%d", itemCount);
		DrawFormatString2F(item.pos_.x-(float)GetDrawStringWidth(item.levelName_.c_str(), item.levelName_.size())/2, (item.pos_.y - WIN_HEIGHT / 2 * item.size_.y) - 50, 0xffffff, 0xff0000, item.levelName_.c_str());
		itemCount++;
	}

	//仮置き
	//DrawFormatString2F(titleTextPos_.x, titleTextPos_.y, 0xffffff, 0xff0000, "タイトルへ");
	DrawFormatString2F(0, 0, 0xffffff, 0xff0000, "移動:A D\n選択:SPACE");

	if (isNext_ && !isTitleExit_)
	{
		nextPreview_.Draw();
	}

	
	DrawRotaGraph3F(titleTextPos_.x, titleTextPos_.y, GetGraphSize(titleTextruehandle_).x / 2, GetGraphSize(titleTextruehandle_).y / 2, titleTextSize_.x, titleTextSize_.y, 0, titleTextruehandle_, TRUE);

}

void StageSelectScene::Finalize()
{
}


Vector2 StageSelectScene::easeInQuad(Vector2 start, Vector2 end, float time)
{
	//return start + time * time * (end - start);
	return start + ((1 - pow(1 - time, 4)) * (end - start));
}

Vector2 StageSelectScene::GetGraphSize(int32_t GraphHandle)
{

	float x = 0;
	float y = 0;

	GetGraphSizeF(GraphHandle, &x, &y);

	return { x,y };

}