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

	void ChengeTag(const std::list<std::shared_ptr<Object>>::iterator& chengeData, ObjectType tag);

	std::list<std::shared_ptr<Object>> stageObjData_;

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

	//読み込みなおしたとき鍵の追加がしたいときの関数
	void AddKeyNum() { KeyNum_++; };

	//鍵の数の指定がしたいときの関数
	void SetKeyNum(int32_t num) { KeyNum_ = num; };

	void SetNextStageSelect(int32_t nextStageSelect) { nextStageSelect_ = nextStageSelect; }

	/// <summary>
	/// 次どうするかを決定する
	/// </summary>
	/// <param name="selectRetrun">false=次のステージへ,true=ステージセレクトへ</param>
	void NextSelect(bool selectReturn);

	//今読み込んでるステージを読み込みなおす
	void NowStageReset();

	//テスト時のオブジェクト保持用
	std::shared_ptr<Object> TestSaveSelectObject(Object object);

	std::unique_ptr<Object> SelectObject(ObjectType tag);

	//現在読み込んでいるjson内にあるLevelNameを返す関数
	std::string GetNowLevelNameInjson() { return nowLevelStageName_; };

	//ウインドウの標準機能で読み込むファイルを指定してそれを返す(importLevelと違うところはファイル内のLevelNameを更新するか)
	InputLevelData WindowsOpenLevelFileToStageManager();

private:

	//シングルトン用
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

	Vector2 GetGraphSize(int32_t GraphHandle);


private:

	//エミッター
	ConfettiEmiitter confettiEmitter;

	//ステージとして追加したいファイル名を保持
	std::vector<std::string> stageFileName_;

	//読み込んだ時ソートしたいのでそれの保持用
	std::list<std::shared_ptr<Object>> stageObjUnSortData_;

	//現在読み込んでいるステージの位置
	uint32_t nowLevelNum_ = 0;
	
	//エディタ使ってる？
	bool isUseEditer_ = false;

	//ステージの鍵の数
	int32_t KeyNum_ = 0;

	bool isClear_ = false;

	bool isNextLoad_ = false;

	//イージング用のタイマー
	float easingFrame_ = 0;
	float maxEasingFrame_ = 50;

	//クリア時の画像用
	float clearTextSize_ = 0;

	uint32_t clearTextTextruehandle1_ = 0;
	uint32_t clearTextTextruehandle2_ = 0;
	uint32_t clearTextTextruehandle3_ = 0;
	uint32_t SelectClearTextTextruehandle2_ = 0;
	uint32_t SelectClearTextTextruehandle3_ = 0;
	uint32_t SelectClearTextTextruehandle4_ = 0;
	uint32_t SelectClearTextTextruehandle5_ = 0;

	int32_t nextStageSelect_ = 0;

	//現在読み込んでいるjson内にあるLevelName
	std::string nowLevelStageName_ = "";

};

