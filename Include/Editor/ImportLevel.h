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

class ImportLevel
{
public:
	ImportLevel();
	~ImportLevel();

	//取ってきたデータを既定の配列に入れる
	//データをvector配列に入れる
	static std::vector<LevelData> ImportLevelVectorData(const std::string& fileName);
	//データをlist配列に入れる
	static std::list<LevelData> ImportLevelListData(const std::string& fileName);

	//レベルの中身読み込むよう
	static LevelData LevelScanning(nlohmann::json& Level);


private:

};

