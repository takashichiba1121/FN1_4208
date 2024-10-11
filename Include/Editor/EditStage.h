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

	void WindowsSaveFile(std::vector<std::unique_ptr<Object>> saveData);
	void WindowsSaveFile(std::list<std::unique_ptr<Object>> saveData);

	void SaveLevelFullPathData(const std::string& fileName, std::vector<std::unique_ptr<Object>> saveData);
	void SaveLevelFullPathData(const std::string& fileName, std::list<std::unique_ptr<Object>> saveData);


private:



};

