#include "DxLib.h"
#include "Input.h"
#include "Window.h"
#include "SceneManager.h"
#include"SceneFactrory.h"
#include "SceneChangeFactory.h"
#include "ImGuiManager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include"TextureManager.h"
#include"SoundManager.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

	return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	SetOutApplicationLogValidFlag(false);
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	DxLib::WaitVSync(true);
	DxLib::SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib::SetHookWinProc(WndProc);
	DxLib::SetAlwaysRunFlag(true);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾


	ImGuiManager::GetInstance()->Initialize();

	// ������
	Input::Initialize();
	SceneManager::GetInstance()->SetSceneFactory(SceneFactrory::GetInstance());
	SceneManager::GetInstance()->SetSceneChangeFactory(SceneChangeFactory::GetInstance());

	SceneManager::GetInstance()->ChangeScene("GAME");



	// �Q�[�����[�v
	while (true) {

		// ��ʃN���A
		ClearDrawScreen();
		Input::Update();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		ImGuiManager::GetInstance()->Update();
		SceneManager::GetInstance()->Update();
		ImGuiManager::GetInstance()->End();

		// �`�揈��
		SceneManager::GetInstance()->Draw();
		ImGuiManager::GetInstance()->Draw();
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	SceneManager::GetInstance()->Finalize();

	SoundManager::Instance()->Finalize();

	TextureManager::Instance()->Finalize();
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
