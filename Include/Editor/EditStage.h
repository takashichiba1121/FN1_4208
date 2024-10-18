#pragma once
#include "StageManager.h"

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


private:



};

