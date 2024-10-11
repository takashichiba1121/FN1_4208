#include "EditStage.h"
#include "DxLib.h"
#include <fstream>

EditStage::EditStage()
{
}

EditStage::~EditStage()
{
}

void EditStage::Initialize()
{
	
}

void EditStage::Update()
{
	
}

void EditStage::Draw()
{

}

void EditStage::WindowsSaveFile(std::vector<std::unique_ptr<Object>> saveData)
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//構造体の大きさ基本的にこれ
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//使いたい(占有)ウインドウハンドル
	FileObj.hwndOwner = GetMainWindowHandle();
	//フィルターを設定?
	FileObj.lpstrFilter = "ステージエディタ作成ファイル\0 * .json*\0\0";
	//拡張子決定
	FileObj.lpstrDefExt = "json";
	//何個目のフィルターを使うん?みたいな感じ?
	FileObj.nFilterIndex = 0;
	//保存の時ファイル名を入れるやつ?
	FileObj.lpstrFile = filePath;
	//ファイルのバッファの大きさ？
	FileObj.nMaxFile = MAX_PATH;
	//ファイルを保存するときにどういう動きをするか
	FileObj.Flags = OFN_OVERWRITEPROMPT;

	auto old = std::filesystem::current_path();
	if (GetSaveFileName(&FileObj))
	{
		SaveLevelFullPathData(filePath,saveData);
	}
	std::filesystem::current_path(old);
}

void EditStage::WindowsSaveFile(std::list<std::unique_ptr<Object>> saveData)
{
	char filePath[MAX_PATH] = { 0 };
	OPENFILENAME FileObj = {};
	//構造体の大きさ基本的にこれ
	FileObj.lStructSize = sizeof(OPENFILENAME);
	//使いたい(占有)ウインドウハンドル
	FileObj.hwndOwner = GetMainWindowHandle();
	//フィルターを設定?
	FileObj.lpstrFilter = "ステージエディタ作成ファイル\0 * .json*\0\0";
	//拡張子決定
	FileObj.lpstrDefExt = "json";
	//何個目のフィルターを使うん?みたいな感じ?
	FileObj.nFilterIndex = 0;
	//保存の時ファイル名を入れるやつ?
	FileObj.lpstrFile = filePath;
	//ファイルのバッファの大きさ？
	FileObj.nMaxFile = MAX_PATH;
	//ファイルを保存するときにどういう動きをするか
	FileObj.Flags = OFN_OVERWRITEPROMPT;

	auto old = std::filesystem::current_path();
	if (GetSaveFileName(&FileObj))
	{
		SaveLevelFullPathData(filePath, saveData);
	}
	std::filesystem::current_path(old);
}

void EditStage::SaveLevelFullPathData(const std::string& fileName, std::vector<std::unique_ptr<Object>> saveData)
{
	std::string name = fileName;

	//もし名前が空白なら適当な名前に
	if (fileName == "")
	{
		name = std::string("jsonEventdata");
	}

	nlohmann::json jsonfile;

	//管理名
	jsonfile["name"] = "Level";

	for (auto &levelData : saveData)
	{
		nlohmann::json data;
		
		//objectという固まりの中に情報を入れる
		data["object"]["pos"] = { levelData->GetPos().x,levelData->GetPos().y};
		data["object"]["scale"] = { levelData->GetSize().x,levelData->GetSize().y };
		data["object"]["tag"] = { };
		
		//全体の固まりに入れる
		jsonfile["objects"] += { data };
	}

	//インデントを入れるらしい
	std::ofstream ofs(name);
	if (ofs) {
		ofs << jsonfile.dump(4);
	}
}

void EditStage::SaveLevelFullPathData(const std::string& fileName, std::list<std::unique_ptr<Object>> saveData)
{
	std::string name = fileName;

	//もし名前が空白なら適当な名前に
	if (fileName == "")
	{
		name = std::string("jsonEventdata");
	}

	nlohmann::json jsonfile;

	//管理名
	jsonfile["name"] = "Level";

	for (auto& levelData : saveData)
	{
		nlohmann::json data;

		//objectという固まりの中に情報を入れる
		data["object"]["pos"] = { levelData->GetPos().x,levelData->GetPos().y };
		data["object"]["scale"] = { levelData->GetSize().x,levelData->GetSize().y };
		data["object"]["tag"] = { };

		//全体の固まりに入れる
		jsonfile["objects"] += { data };
	}

	//インデントを入れるらしい
	std::ofstream ofs(name);
	if (ofs) {
		ofs << jsonfile.dump(4);
	}
}