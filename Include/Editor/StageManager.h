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

	void LoadStageObjectFile(const std::string& fileName);

	void Update();

	void Inversion(const float easing);

	void SetTentPos();

	void Draw();

	void AddObject(Vector2 pos, Vector2 size, ObjectType tag);

	void ChengeTag(const std::list<std::unique_ptr<Object>>::iterator& chengeData, ObjectType tag);

	std::list<std::unique_ptr<Object>> stageObjData_;

	bool GetIsUseEditer() { return isUseEditer_; };

	void SetIsUseEditer(bool flag) { isUseEditer_ = flag; };

private:

	//シングルトン用
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

	


private:
	
	bool isUseEditer_ = false;
};

