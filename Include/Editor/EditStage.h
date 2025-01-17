#pragma once
#include "StageManager.h"
#include <imgui.h>
#include "EditorTicket.h"

/*
新しくobjectTypeを追加してエディタに追加したい場合
変更箇所
・EditStage.cppにある ObjectTypeToStringの中身に追加
・stageManager.cpp内にある SelectObjectの中身に追加
・LevelPreView.cpp内にある AddObjectも変更してくれると嬉しい
*/

namespace ImGui
{
#include "vector"
	bool DragFloat2(const char* label, Vector2& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	bool Combo(const std::string& comboName, int32_t& number, std::vector<std::string> items);
}

class EditStage
{
public:
	EditStage();
	~EditStage();

	void Initialize();

	void Update();

	void Draw();

private:

	void WindowsSaveFile(const std::vector<Object*>& saveData);
	void WindowsSaveFile();

	void SaveLevelFullPathData(const std::string& fileName, const std::vector<Object*>& saveData);
	void SaveLevelFullPathData(const std::string& fileName);

	//エディタ用の更新
	void EditorUpdate();

	//imguiのメニュー
	void ImguiMenu();

	//オブジェクト追加
	void addObject();

	//オブジェクト編集
	void EditObject();

	//マウスでオブジェクトを編集するやつ
	void MouseEditObject();

	//今持ってるやつコピーとペースト
	void CopyPasteMouseObject();

	//配置データの保存と読み込み
	void SaveAndLoadLevelObject();

	void Undo();
	void Redo();

	/// <summary>
	/// undoのスタックに追加する
	/// </summary>
	/// <param name="content">変更の種類</param>
	/// <param name="object">変更のあったオブジェクト</param>
	/// <param name="objectNum">変更した位置(種類によっては必要なし)</param>
	void UndoStack(EditContent::Content content, EditContent::TicketData object = {}, int32_t objectNum = 0);

	//objectTypeを渡すとストリングで返してくれる
	std::string ObjectTypeToString(ObjectType objectType);

	//悪いやつなので人のやつコピペ
	bool AABB(Vector2 mousePos, Object* obj);
	bool AABB(Vector2 pos,Vector2 size, Object* obj);

	//テストスタート用の準備
	void TestStart();

	//テストを終えるときの後処理
	void TestEnd();

	//保存時の名前セット用の関数
	void SaveAndSetLevelName();


private:

	ObjectType serectAddObjectType_= ObjectType::NONE;

	Vector2 AddObjectPos_ = { 1,1 };
	Vector2 AddObjectSize_ = { 1,1 };

	InputLevelData loadData;

	bool imguiSaveWindow_ = false;
	bool imguiLoadWindow_ = false;
	bool imguiAddObjectWindow_ = false;

	//マウスがオブジェクトを持っているか
	bool isMouseObject_ = false;

	bool isAddObjectDraw = false;

	int32_t addObjectColor = 0xffffff;
	int32_t mouseSetObjectColor = 0xffffff;

	//マウスでオブジェクトを移動する際の元の位置保持用
	Vector2 oldObjPos_ = {};

	//マウスでオブジェクトを移動する際の移動先
	Vector2 mouseEditObjPos = {};

	Object* mouseMoveObject_ = nullptr;

	Object copyObject_;

	//水平線の位置
	float horizontal_ = 160.0f;

	float startHorizontal_ = 0.0f;

	std::vector<std::unique_ptr<EditorTicket>> undoTickets_;
	std::vector<std::unique_ptr<EditorTicket>> redoTickets_;

	//テスト用の元の位置保持用list
	std::list< std::unique_ptr<Object>> testSaveObject_;

	bool isImguiUse_ = false;

	EditContent::TicketData movedata_;

	int32_t mouseMoveObjectUndoObjectNum_ = 0;

	//ステージセレクトで描画用の文字
	std::string LevelName_ = "";

	char str1[128] = "";
};

