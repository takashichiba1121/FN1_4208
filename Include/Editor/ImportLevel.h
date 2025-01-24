#pragma once
//レベルデータを読み込んで返すクラス

#include "DxLib.h"
#include "Vector2.h"
#include "vector"
#include <memory>
#include "Object.h"

//jsonの読み込みとかに使う
#pragma warning( push )
#pragma warning( disable : 26819 )
#include "json.hpp"
#pragma warning( pop )

struct LevelData
{
	//基本情報
	Vector2 pos;
	Vector2 scale;

	nlohmann::json seting;

	//中身(後でenumに変えるかも)
	ObjectType tag = ObjectType::PLAYER;
};

//読み込んだ時帰ってくるデータ
struct InputLevelData
{
	std::list<LevelData> levelData;

	//ステージの名前とか説明とか
	std::string LevelName_ = "";

	float horizontal = 0.0f;

	bool isLoad = false;

};


struct ObjectName
{
	//数字を対応したenumclassで返す関数
	template <typename Enum>
	static Enum ObjectString(int value) {
	for (int32_t i = static_cast<int32_t>(ObjectType::PLAYER); i <= static_cast<int32_t>(ObjectType::NONE); i++) 
	{
			if (i == value) 
			{
				return static_cast<Enum>(i);
			}
		}
		return static_cast<Enum>(ObjectType::NONE);
	}
};

class ImportLevel
{
public:
	//おい俺はシングルトンだぞ
	static ImportLevel* GetInstance();

	

	InputLevelData WindowsOpenLevelFile();

	//データをlist配列に入れる
	InputLevelData ImportLevelListData(const std::string& fileName);
	InputLevelData ImportLevelListDataFullPath(const std::string& fileName);

	std::string GetLoadErrorText() { return loadErrorText_; };
	
private:

	//シングルトン用
	ImportLevel() = default;
	~ImportLevel();

	ImportLevel(const ImportLevel&) = delete;
	ImportLevel& operator=(const ImportLevel&) = delete;
	
	//レベルの中身読み込むよう
	bool LevelScanning(nlohmann::json& Level);

private:

	//一時保存用です基本的に中身なし
	std::vector<LevelData> vectorLevelData_;
	std::list<LevelData> listLevelData_;

	std::string loadErrorText_;

	//読み込む際のファイルパス(ファイル名だけで指定するため)
	static const inline std::string SDefaultEventPath_ = "Resources/Level/";

	//ファイル拡張子
	static const inline std::string SDefaultEventExtension_ = ".json";

};

