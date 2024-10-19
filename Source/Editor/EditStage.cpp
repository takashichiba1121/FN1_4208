#include "EditStage.h"
#include "DxLib.h"
#include <fstream>

#include "Input.h"

bool ImGui::DragFloat2(const char* label, Vector2& v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	float vf[2] = { v.x,v.y };
	bool result = false;
	result= ImGui::DragFloat2(label, vf, v_speed, v_min, v_max, format, flags);

	if (result)
	{
		v = { vf[0],vf[1] };
	}
	return result;
}

bool ImGui::Combo(const std::string& comboName, int32_t& number, std::vector<std::string> items)
{
	std::vector<const char*> tmp;

	for (const auto& item : items)
	{
		tmp.push_back(item.c_str());
	}

	return ImGui::Combo(comboName.c_str(), &number, tmp.data(), int32_t(items.size()));
}

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
	EditorUpdate();
}

void EditStage::Draw()
{

}

void EditStage::EditorUpdate()
{
	addObject();

	ImguiMenu();

	EditObject();
}

void EditStage::ImguiMenu()
{
	//imguiの機能を追加するためのフラグ
	ImGuiWindowFlags window_flags = 0;
	//メニューバーを使います
	window_flags |= ImGuiWindowFlags_MenuBar;
	//beginで渡すことでフラグをこのウインドウで有効にする
	ImGui::Begin("Editor", NULL, window_flags);


	//エディタの機能をまとめたメニュー
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File\n"))
		{
			ImGui::MenuItem("EventSave", NULL, &imguiSaveWindow_);
			ImGui::MenuItem("EventLoad", NULL, &imguiLoadWindow_);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("addEvent\n"))
		{
			imguiAddObjectWindow_ = true;
			ImGui::EndMenu();
		}

		ImGui::Text("%0.0fFPS", ImGui::GetIO().Framerate);
		ImGui::EndMenuBar();
	}

	SaveAndLoadLevelObject();

	ImGui::End();
}

void EditStage::addObject()
{

	if (!imguiAddObjectWindow_)return;

	if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
	{
		AddObjectPos_ = Input::GetMousePos();
	}

	if (!ImGui::Begin("addObject", &imguiAddObjectWindow_))
	{
		ImGui::End();
		return;
	}

	std::vector<std::string>items;
	items.resize(static_cast<int32_t>(ObjectType::NONE));

	int32_t oldObjectType = static_cast<int32_t>(serectAddObjectType_);

	for (size_t i = 0; i < items.size(); i++)
	{
		items[i] = ObjectTypeToString(ObjectType(i));
	}
	int32_t objectType = static_cast<int32_t>(serectAddObjectType_);

	//設定したいイベントの番号にする
	ImGui::Combo("object Type", objectType, items);

	if (oldObjectType != objectType)
	{
		serectAddObjectType_ = ObjectName::ObjectString(objectType);
	}

	ImGui::DragFloat2("Pos", AddObjectPos_, 1.0f, -1000.0f, 1000.0f);
	ImGui::DragFloat2("Size", AddObjectSize_, 1.0f, 1.0f, 1000.0f);

	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) && ImGui::Button("addObject"))
	{
		StageManager::GetInstance()->AddObject(AddObjectPos_, AddObjectSize_, serectAddObjectType_);
	}

	if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) && Input::GetMouseKeyTrigger(Input::MouseKey::RIGHT))
	{
		StageManager::GetInstance()->AddObject(Input::GetMousePos(), AddObjectSize_, serectAddObjectType_);
	}

	ImGui::End();

}

void EditStage::EditObject()
{
	ImGui::Begin("EditObject");

	uint16_t eventCount = 0;

	for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end();)
	{

		std::string num = ("##" + std::to_string(eventCount));

		if (!ImGui::CollapsingHeader(std::string("eventNum" + std::to_string(eventCount) + num).c_str()))
		{
			eventCount++;
			objectI++;
			continue;
		}
		ImGui::Text(std::string("ObjectType:" + ObjectTypeToString(objectI->get()->GetObjectType())).c_str());

		Vector2 editPos = objectI->get()->GetPos();
		Vector2 editSize = objectI->get()->GetSize();

		ImGui::DragFloat2("Pos", editPos, 1.0f, -1000.0f, 1000.0f);
		ImGui::DragFloat2("Size", editSize, 1.0f, 1.0f, 1000.0f);

		objectI->get()->SetPos(editPos);
		objectI->get()->SetSize(editSize);
		//StageManager::GetInstance()->stageObjData_.erase(objectI);

		objectI++;
	}

	ImGui::End();
}

void EditStage::WindowsSaveFile(const std::vector<Object*>& saveData)
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

void EditStage::WindowsSaveFile()
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
		SaveLevelFullPathData(filePath);
	}
	std::filesystem::current_path(old);
}

void EditStage::SaveLevelFullPathData(const std::string& fileName, const std::vector<Object*>& saveData)
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
		data["object"]["tag"] = static_cast<int32_t>(levelData->GetObjectType());
		
		//全体の固まりに入れる
		jsonfile["objects"] += { data };
	}

	//インデントを入れるらしい
	std::ofstream ofs(name);
	if (ofs) {
		ofs << jsonfile.dump(4);
	}
}

void EditStage::SaveLevelFullPathData(const std::string& fileName)
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

	for (auto& levelData : StageManager::GetInstance()->stageObjData_)
	{
		nlohmann::json data;

		//objectという固まりの中に情報を入れる
		data["object"]["pos"] = { levelData->GetPos().x,levelData->GetPos().y };
		data["object"]["scale"] = { levelData->GetSize().x,levelData->GetSize().y };
		data["object"]["tag"] = static_cast<int32_t>(levelData->GetObjectType());

		//全体の固まりに入れる
		jsonfile["objects"] += { data };
	}

	//インデントを入れるらしい
	std::ofstream ofs(name);
	if (ofs) {
		ofs << jsonfile.dump(4);
	}
}

void EditStage::SaveAndLoadLevelObject()
{

	if (imguiSaveWindow_)
	{
		WindowsSaveFile();
		imguiSaveWindow_ = false;
	}
	if (imguiLoadWindow_)
	{
		loadData = ImportLevel::GetInstance()->WindowsOpenLevelFileList();
		if (loadData.isLoad)
		{
			StageManager::GetInstance()->LoadListStageData(loadData.levelData);
		}
		imguiLoadWindow_ = false;
	}

	if (!loadData.isLoad && ImportLevel::GetInstance()->GetLoadErrorText() != "")
	{
		ImGui::Text("Loading failed");
		ImGui::Text(std::string("reason " + ImportLevel::GetInstance()->GetLoadErrorText()).c_str());
	}
}



std::string EditStage::ObjectTypeToString(ObjectType objectType)
{
	switch (objectType) {
	case ObjectType::PLAYER:   return "player";
	case ObjectType::FLOAT_BLOCK: return "floatBlock";
	case ObjectType::NOT_FLOAT_BLOCK: return "notFloatBlock";
	default:    return "UNKNOWN";
	}
}