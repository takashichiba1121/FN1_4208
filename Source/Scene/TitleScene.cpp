#include "TitleScene.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "Input.h"
#include <DxLib.h>

void TitleScene::Initialize()
{
	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\PressSpace.png");

	for (int i = 0; i < 3; i++) {

		titleLogo[i] = std::make_unique<TitleLogo>();
		titleLogo[i]->Initialize(i);
	}
}

void TitleScene::Update()
{
	if (Input::GetKeyTrigger(Input::Key::Space)) {
		SceneManager::GetInstance()->ChangeScene("STAGESELECT");
	}

	for (int i = 0; i < 3; i++) {
		titleLogo[i]->SetPos({WIN_WIDTH / 2 + 300 * (float)(i - 1) ,Water::GetInstance()->GetHorizontal()});
		titleLogo[i]->Update();
	}
	Water::GetInstance()->Update();
}

void TitleScene::Draw()
{
	for (std::unique_ptr<TitleLogo>& logo : titleLogo) {
		logo->Draw();
	}
	
	Water::GetInstance()->Draw();

	DrawGraph(WIN_WIDTH / 2 - 256, 550, textruehandle_,true);
}

void TitleScene::Finalize()
{
}
