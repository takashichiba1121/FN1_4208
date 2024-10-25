#pragma once
#include "StageManager.h"
#include <imgui.h>

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

	//配置データの保存と読み込み
	void SaveAndLoadLevelObject();

	//objectTypeを渡すとストリングで返してくれる
	std::string ObjectTypeToString(ObjectType objectType);

	//悪いやつなので人のやつコピペ
	bool AABB(Vector2 mousePos, Object* obj);
	bool AABB(Vector2 pos,Vector2 size, Object* obj);


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

};

