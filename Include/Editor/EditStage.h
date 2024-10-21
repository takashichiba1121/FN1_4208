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

	void ImguiMenu();

	void addObject();

	void SaveAndLoadLevelObject();

	std::string ObjectTypeToString(ObjectType objectType);


private:

	ObjectType serectAddObjectType_= ObjectType::NONE;

	Vector2 AddObjectPos_ = { 1,1 };
	Vector2 AddObjectSize_ = { 1,1 };

	InputLevelData loadData;

	bool imguiSaveWindow_ = false;
	bool imguiLoadWindow_ = false;
	bool imguiAddObjectWindow_ = false;

};

