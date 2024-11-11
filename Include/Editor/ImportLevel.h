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

	//中身(後でenumに変えるかも)
	ObjectType tag = ObjectType::PLAYER;
};

//読み込んだ時帰ってくるデータ
struct InputLevelData
{
	std::list<LevelData> levelData;

	float horizontal = 0.0f;

	bool isLoad = false;

};


struct ObjectName
{
	static ObjectType ObjectString(int32_t objectNum)
	{
		if (objectNum == static_cast<int32_t>(ObjectType::PLAYER))
		{
			return ObjectType::PLAYER;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::FLOAT_BLOCK))
		{
			return ObjectType::FLOAT_BLOCK;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::NOT_FLOAT_BLOCK))
		{
			return ObjectType::NOT_FLOAT_BLOCK;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::BREAK_BLOCK))
		{
			return ObjectType::BREAK_BLOCK;
		}
		else if (objectNum == static_cast<int32_t>(ObjectType::GOAL))
		{
			return ObjectType::GOAL;
		}

		return ObjectType::NONE;
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

	std::string GetLoadErrorText() { return loadErrorText_; };
	
private:

	//シングルトン用
	ImportLevel() = default;
	~ImportLevel();

	ImportLevel(const ImportLevel&) = delete;
	ImportLevel& operator=(const ImportLevel&) = delete;


	//取ってきたデータを既定の配列に入れる
	//データをvector配列に入れる
	//InputLevelData ImportLevelVectorData(const std::string& fileName);
	
	//レベルの中身読み込むよう
	bool LevelScanning(nlohmann::json& Level);

private:

	//一時保存用です基本的に中身なし
	std::vector<LevelData> vectorLevelData_;
	std::list<LevelData> listLevelData_;

	std::string loadErrorText_;

};

