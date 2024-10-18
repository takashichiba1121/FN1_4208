#pragma once
#include "DxLib.h"
#include "Object.h"
#include "ImportLevel.h"
#include <vector>
#include <memory>
#include <list>
#include <sstream>

class StageManager
{
public:
	//おい俺はシングルトンだぞ
	static StageManager* GetInstance();

	std::vector<Object> LoadStageData(const std::string& fileName);
	void LoadListStageData(std::list<LevelData> levelData);

	void Update();

	void Draw();

	

private:

	//シングルトン用
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

	//エディタ用の更新
	void EditorUpdate();

	void addObject(Vector2 pos, Vector2 size, ObjectType tag);


private:
	std::list<std::unique_ptr<Object>> stageObjData_;

};

