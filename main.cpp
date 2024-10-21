#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include"SceneFactrory.h"
#include "ImGuiManager.h"
#include "imgui.h"
#include "Goal.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	Goal* goal = new Goal();


	//ImGuiManager::GetInstance()->Initialize();

	// 初期化
	Input::Initialize();
	SceneManager::GetInstance()->SetSceneFactory(SceneFactrory::GetInstance());

	SceneManager::GetInstance()->ChangeScene("GAME");
	goal->Initialize();
	// ゲームループ
	while (true) {

		// 画面クリア
		ClearDrawScreen();
		Input::Update();
		
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		//ImGuiManager::GetInstance()->Update();
		SceneManager::GetInstance()->Update();
		goal->Update();

		// 描画処理
		SceneManager::GetInstance()->Draw();
		goal->Draw();
		//ImGuiManager::GetInstance()->Draw();
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
