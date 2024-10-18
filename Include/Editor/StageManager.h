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

	std::list<Object*> GetObjectList() { return stageObjData_; };

	//登録
	void SetObjectList(const std::list<Object*>& list) { stageObjData_ = list; };

	void Update();

	void Draw();

	

private:

	//シングルトン用
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

	void addObject(Vector2 pos, Vector2 size, ObjectType tag);


private:
	std::list<Object*> stageObjData_;

};

