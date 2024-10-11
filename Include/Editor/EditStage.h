#pragma once
#include "StageManager.h"

class EditStage
{
public:
	EditStage();
	~EditStage();

private:

	void WindowsSaveEEFMFile(std::vector<Object*> saveData);
	void WindowsSaveEEFMFile(std::list<Object*> saveData);

	void SaveEventFullPathData(const std::string& fileName, std::vector<Object*> saveData);


};

