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

	//�G�f�B�^�p�̍X�V
	void EditorUpdate();

	void addObject();

	void SaveAndLoadLevelObject();


private:

	ObjectType serectAddObjectType_;

	Vector2 AddObjectSize_ = { 1,1 };

};

