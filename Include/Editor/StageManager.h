#pragma once
#include "DxLib.h"
#include "Object.h"
#include "ImportLevel.h"
#include <vector>
#include <memory>
#include <list>
#include <sstream>
#include "ConfettiEmiitter.h"

class StageManager
{
public:
	//おい俺はシングルトンだぞ
	static StageManager* GetInstance();

	//std::vector<Object> LoadStageData(const std::string& fileName);
	void LoadListStageData(std::list<LevelData> levelData);

	void LoadStageObjectFile(const std::string& fileName);

	void Initialize();

	void Update();

	void Inversion(const float easing);

	void SetTentPos();

	void Draw();

	void AddObject(Vector2 pos, Vector2 size, ObjectType tag);
	void AddObject(Vector2 pos, Vector2 size, ObjectType tag, nlohmann::json seting);

	void ChengeTag(const std::list<std::unique_ptr<Object>>::iterator& chengeData, ObjectType tag);

	std::list<std::unique_ptr<Object>> stageObjData_;

	bool GetIsUseEditer() { return isUseEditer_; };

	void SetIsUseEditer(bool flag) { isUseEditer_ = flag; };

	int32_t GetStageFileNameNum() { return stageFileName_.size(); };

	int32_t GetNowLevelNum() { return nowLevelNum_; };

	void SelectLevelNum(int32_t selectNum);

	void NextLevelLoad();

	bool GetIsClear() { return isClear_; };

	void SetIsClear(bool flag) { isClear_ = flag; };

	std::string GetStageFileName(int32_t num) { return stageFileName_[num]; };

	//鍵の数を取得
	int32_t GetKeyNum() { return KeyNum_; };

	//鍵を取得したので鍵の数を減らす関数
	void GetKey() { KeyNum_--; };

	/// <summary>
	/// 次どうするかを決定する
	/// </summary>
	/// <param name="selectRetrun">false=次のステージへ,true=ステージセレクトへ</param>
	void NextSelect(bool selectReturn);

private:

	//シングルトン用
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

	std::unique_ptr<Object> SelectObject(ObjectType tag);


private:

	//エミッター
	ConfettiEmiitter confettiEmitter;

	//ステージとして追加したいファイル名を保持
	std::vector<std::string> stageFileName_;

	uint32_t nowLevelNum_ = 0;
	
	bool isUseEditer_ = false;

	int32_t KeyNum_ = 0;

	bool isClear_ = false;

	bool isNextLoad_ = false;

	float easingFrame_ = 0;
	float maxEasingFrame_ = 50;

	float clearTextSize_ = 0;

	uint32_t clearTextTextruehandle1_;
	uint32_t clearTextTextruehandle2_;
	uint32_t clearTextTextruehandle3_;
};

