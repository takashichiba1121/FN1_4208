#pragma once
#include "StageManager.h"
#include <imgui.h>

namespace ImGui
{
#include "vector"
	bool DragFloat2(const char* label, Vector2 v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	bool Combo(const std::string& comboName, int32_t& number, std::vector<std::string> items);
}

struct ObjectName
{
	static ObjectType ObjectString(int32_t objectNum)
	{
		if (objectNum == static_cast<int32_t>(ObjectType::PLAYER))
		{
			return ObjectType::PLAYER;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::FLOAT_BLOCK))
		{
			return ObjectType::FLOAT_BLOCK;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::NOT_FLOAT_BLOCK))
		{
			return ObjectType::NOT_FLOAT_BLOCK;
		}

		return ObjectType::NONE;
	}
};

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
	void WindowsSaveFile(const std::list<Object*>& saveData);

	void SaveLevelFullPathData(const std::string& fileName, const std::vector<Object*>& saveData);
	void SaveLevelFullPathData(const std::string& fileName, const std::list<Object*>& saveData);

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

