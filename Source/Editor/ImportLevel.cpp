#include "ImportLevel.h"
#include <sstream>
#include <fstream>
#include <cstdint>
#include<string>

ImportLevel::ImportLevel()
{
}

ImportLevel::~ImportLevel()
{
}

std::vector<LevelData> ImportLevel::ImportLevelVectorData(const std::string& fileName)
{

	std::vector<LevelData> levelData;
	//ファイルストリーム
	std::ifstream file(fileName);

	if (!file)
	{
		assert(0);
	}

	//JSON文字列から解凍したデータ
	nlohmann::json deserialized;

	//解凍
	file >> deserialized;

	//正しいイベントファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//"name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();

	//中身が正しいかどうかチェック
	assert(name.compare("Level") == 0);

	//"events"の全オブジェクトを走査
	for (nlohmann::json& objects : deserialized["objects"])
	{

		levelData.push_back(LevelScanning(objects));
	}
	
	if (levelData.empty())
	{
		levelData.push_back(LevelData());
	}

	return levelData;
}

std::list<LevelData> ImportLevel::ImportLevelListData(const std::string& fileName)
{
	std::list<LevelData> levelData;
	//ファイルストリーム
	std::ifstream file(fileName);

	if (!file)
	{
		assert(0);
	}

	//JSON文字列から解凍したデータ
	nlohmann::json deserialized;

	//解凍
	file >> deserialized;

	//正しいイベントファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	//"name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();

	//中身が正しいかどうかチェック
	assert(name.compare("Level") == 0);

	//"events"の全オブジェクトを走査
	for (nlohmann::json& objects : deserialized["objects"])
	{

		levelData.push_back(LevelScanning(objects));
	}

	if (levelData.empty())
	{
		levelData.push_back(LevelData());
	}

	return levelData;
}

LevelData ImportLevel::LevelScanning(nlohmann::json& Level)
{


	LevelData levelData;

	//設定のパラメータ読み込み
	nlohmann::json& seting = Level["object"];

	//移動する場所読み込み
	levelData.pos.x = (float)seting["pos"][0];
	levelData.pos.y = (float)seting["pos"][1];

	//移動開始位置取得
	levelData.scale.x = (float)seting["scale"][0];
	levelData.scale.y = (float)seting["scale"][1];

	//スピードのセット
	levelData.tag = (ObjectType)seting["tag"];

	return levelData;
	
}
