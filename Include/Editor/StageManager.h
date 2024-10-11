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

	//std::vector<Object> LoadStageData(const std::string& fileName);
	std::list<Object*> LoadListStageData(std::list<LevelData> levelData);

	//今読み込んでるデータを返す
	std::list<Object*> GetObjectList() { return stageObjData_; };

	void Update();

	void Draw();

private:

	//シングルトン用
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

private:

	std::list<Object*> stageObjData_;

};

