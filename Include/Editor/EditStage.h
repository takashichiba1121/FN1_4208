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

	void WindowsSaveFile(const std::vector<std::unique_ptr<Object>>& saveData);
	void WindowsSaveFile(const std::list<std::unique_ptr<Object>>& saveData);

	void SaveLevelFullPathData(const std::string& fileName, const std::vector<std::unique_ptr<Object>>& saveData);
	void SaveLevelFullPathData(const std::string& fileName, const std::list<std::unique_ptr<Object>>& saveData);


private:



};

