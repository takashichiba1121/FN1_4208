#include "TitleScene.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "Input.h"
#include <DxLib.h>

void TitleScene::Initialize()
{
	Water::GetInstance()->SetHorizontal(320);
	soundPlayManager = SoundPlayManager::Instance();

	textruehandle_ = TextureManager::Instance()->LoadTexture("Resources\\Texture\\PressSpace.png");

	for (int i = 0; i < 3; i++) {

		titleLogo[i] = std::make_unique<TitleLogo>();
		titleLogo[i]->Initialize(i);
	}

	if (!CheckSoundMem(soundPlayManager->GetBGM().titleScene)) {
		soundPlayManager->BGMStop(soundPlayManager->GetBGM().gameScene);
		soundPlayManager->BGMPlay(soundPlayManager->GetBGM().titleScene, 100);
	}
}

void TitleScene::Update()
{
	if (Input::GetKeyTrigger(Input::Key::Space) || Input::TriggerPadKey(PAD_INPUT_1)) {
		SceneManager::GetInstance()->ChangeScene("STAGESELECT");
		soundPlayManager->SoundPlay(soundPlayManager->GetSound().inversionA, 100);
	}

	//ƒKƒCƒhUI‚Ì“§–¾“x
	if (guideTrans >= 255.0f) {
		drawGuide = false;
	}
	if (guideTrans <= 0.0f) {
		drawGuide = true;
	}

	if (drawGuide) {
		guideTrans += 255.0f / 30.0f;
	}
	else {
		guideTrans -= 255.0f / 30.0f;
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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, guideTrans);
	DrawGraph(WIN_WIDTH / 2 - 256, 550, textruehandle_,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::Finalize()
{
}
