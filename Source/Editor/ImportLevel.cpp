#include "ImportLevel.h"
#include <sstream>
#include <fstream>
#include <cstdint>
#include<string>

ImportLevel* ImportLevel::GetInstance()
{
	static ImportLevel instance;
	return &instance;
}
ImportLevel::~ImportLevel()
{
}

InputLevelData ImportLevel::ImportLevelVectorData(const std::string& fileName)
{

	vectorLevelData_.clear();

	InputLevelData output;

	//ファイルストリーム
	std::ifstream file(fileName);

	if (!file)
	{
		loadErrorText_ = "can not find file";
		output.isLoad = false;
		return output;
	}

	//JSON文字列から解凍したデータ
	nlohmann::json deserialized;

	//解凍
	file >> deserialized;

	//正しいイベントファイルかチェック
	if (!deserialized.is_object() || !deserialized.contains("name") || !deserialized["name"].is_string())
	{
		loadErrorText_ = "Not the correct Level file";
		output.isLoad = false;
		return output;
	}

	//"name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();

	//正しいかどうかチェック
	if (name.compare("Level") != 0)
	{
		loadErrorText_ = "Not LevelEditor file";
		output.isLoad = false;
		return output;
	}

	//"events"の全オブジェクトを走査
	for (nlohmann::json& events : deserialized["objects"])
	{

		bool result = true;

		result = LevelScanning(events);

		if (!result)
		{
			vectorLevelData_.clear();
			output.isLoad = false;
			return output;
		}
	}


	if (vectorLevelData_.empty())
	{
		vectorLevelData_.push_back(LevelData());
	}

	loadErrorText_ = "";
	output.levelData = listLevelData_;
	output.isLoad = true;

	listLevelData_.clear();
	vectorLevelData_.clear();
	return output;
}

InputLevelData ImportLevel::ImportLevelListData(const std::string& fileName)
{
	listLevelData_.clear();

	InputLevelData output;

	//ファイルストリーム
	std::ifstream file(fileName);

	if (!file)
	{
		loadErrorText_ = "can not find file";
		output.isLoad = false;
		return output;
	}

	//JSON文字列から解凍したデータ
	nlohmann::json deserialized;

	//解凍
	file >> deserialized;

	//正しいイベントファイルかチェック
	if (!deserialized.is_object() || !deserialized.contains("name") || !deserialized["name"].is_string())
	{
		loadErrorText_ = "Not the correct Level file";
		output.isLoad = false;
		return output;
	}

	//"name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();

	//正しいかどうかチェック
	if (name.compare("Level") != 0)
	{
		loadErrorText_ = "Not LevelEditor file";
		output.isLoad = false;
		return output;
	}

	//"events"の全オブジェクトを走査
	for (nlohmann::json& events : deserialized["objects"])
	{

		bool result = true;

		result = LevelScanning(events);

		if (!result)
		{
			listLevelData_.clear();
			output.isLoad = false;
			return output;
		}
	}


	if (listLevelData_.empty())
	{
		listLevelData_.push_back(LevelData());
	}

	loadErrorText_ = "";
	output.levelData = listLevelData_;
	output.isLoad = true;

	listLevelData_.clear();
	vectorLevelData_.clear();
	return output;
}

bool ImportLevel::LevelScanning(nlohmann::json& Level)
{

	////typeがなければ止める
	//if (!Level.contains("type"))
	//{
	//	loadErrorText_ = "event type is missing";
	//	return false;
	//}
	////タイプを取得
	//std::string type = Level["type"].get<std::string>();



	LevelData levelData;

	//設定のパラメータ読み込み
	nlohmann::json& seting = Level["object"];

	//位置読み込み
	levelData.pos.x = (float)seting["pos"][0];
	levelData.pos.y = (float)seting["pos"][1];

	//大きさ取得
	levelData.scale.x = (float)seting["scale"][0];
	levelData.scale.y = (float)seting["scale"][1];

	//種類
	levelData.tag = ObjectName::ObjectString((int32_t)seting["tag"]);

	vectorLevelData_.push_back(levelData);
	listLevelData_.push_back(levelData);

	return true;

	
}


InputLevelData ImportLevel::WindowsOpenLevelFileVector()
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//構造体の大きさ基本的にこれ
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//使いたい(占有)ウインドウハンドル
	FileObj.hwndOwner = GetMainWindowHandle();
	//フィルターを設定?
	FileObj.lpstrFilter = "ステージエディタ作成ファイル\0 * .json*\0"
		"すべてのファイル (*.*)\0*.*\0";
	//何個目のフィルターを使うん?みたいな感じ?
	FileObj.nFilterIndex = 0;
	//保存の時ファイル名を入れるやつ?
	FileObj.lpstrFile = filePath;
	//ファイルのバッファの大きさ？
	FileObj.nMaxFile = MAX_PATH;

	auto old = std::filesystem::current_path();
	InputLevelData result;
	if (GetOpenFileName(&FileObj))
	{
		//設定のまとめに選択したファイルを読み取り書き込む
		result = ImportLevelVectorData(filePath);

		if (!result.isLoad)
		{
			return result;
		}

	}
	std::filesystem::current_path(old);
	result.levelData = listLevelData_;
	result.isLoad = true;
	return result;
}

InputLevelData ImportLevel::WindowsOpenLevelFileList()
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//構造体の大きさ基本的にこれ
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//使いたい(占有)ウインドウハンドル
	FileObj.hwndOwner = GetMainWindowHandle();
	//フィルターを設定?
	FileObj.lpstrFilter = "ステージエディタ作成ファイル\0 * .json*\0"
		"すべてのファイル (*.*)\0*.*\0";
	//何個目のフィルターを使うん?みたいな感じ?
	FileObj.nFilterIndex = 0;
	//保存の時ファイル名を入れるやつ?
	FileObj.lpstrFile = filePath;
	//ファイルのバッファの大きさ？
	FileObj.nMaxFile = MAX_PATH;

	auto old = std::filesystem::current_path();
	InputLevelData result;
	if (GetOpenFileName(&FileObj))
	{
		//設定のまとめに選択したファイルを読み取り書き込む
		result = ImportLevelListData(filePath);

		if (!result.isLoad)
		{
			return result;
		}

	}
	std::filesystem::current_path(old);

	result.levelData = listLevelData_;
	result.isLoad = true;
	return result;
}