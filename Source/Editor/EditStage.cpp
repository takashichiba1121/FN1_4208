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
	if (isMouseObject_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBoxAA(mouseEditObjPos.x - mouseMoveObject_->GetSize().x / 2, mouseEditObjPos.y - mouseMoveObject_->GetSize().y / 2, mouseEditObjPos.x + mouseMoveObject_->GetSize().x / 2, mouseEditObjPos.y + mouseMoveObject_->GetSize().y / 2, mouseSetObjectColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (isAddObjectDraw)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBoxAA(AddObjectPos_.x - AddObjectSize_.x / 2, AddObjectPos_.y - AddObjectSize_.y / 2, AddObjectPos_.x + AddObjectSize_.x / 2, AddObjectPos_.y + AddObjectSize_.y / 2, addObjectColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void EditStage::EditorUpdate()
{
	addObject();

	ImguiMenu();

	EditObject();

	CopyPasteMouseObject();
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
			ImGui::MenuItem("ObjectSave", NULL, &imguiSaveWindow_);
			ImGui::MenuItem("ObjectLoad", NULL, &imguiLoadWindow_);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("addObject\n"))
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
	isAddObjectDraw = false;
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

	if (isMouseObject_)
	{
		ImGui::End();
		return;
	}

	isAddObjectDraw = true;

	for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
	{
		if (AABB(AddObjectPos_, AddObjectSize_, objectI->get()))
		{
			addObjectColor = 0xff0000;
			ImGui::End();
			return;
		}
	}
	
	addObjectColor = 0xffffff;
	if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
	{
		//imguiの機能を追加するためのフラグ
		ImGuiWindowFlags window_flags = 0;
		//メニューバーを使います
		window_flags |= ImGuiWindowFlags_MenuBar;
		//beginで渡すことでフラグをこのウインドウで有効にする
		ImGui::Begin("Editor", NULL, window_flags);
		ImGui::Text("set: Rightclick");
		ImGui::End();
	}

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
	MouseEditObject();
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

		std::vector<std::string>items;
		items.resize(static_cast<int32_t>(ObjectType::NONE));

		int32_t oldObjectType = static_cast<int32_t>(objectI->get()->GetObjectType());

		for (size_t i = 0; i < items.size(); i++)
		{
			items[i] = ObjectTypeToString(ObjectType(i));
		}
		int32_t objectType = static_cast<int32_t>(objectI->get()->GetObjectType());

		//設定したいイベントの番号にする
		ImGui::Combo("object Type", objectType, items);

		if (oldObjectType != objectType)
		{
			StageManager::GetInstance()->ChengeTag(objectI, ObjectName::ObjectString(objectType));
		}
		

		Vector2 editPos = objectI->get()->GetPos();
		Vector2 editSize = objectI->get()->GetSize();

		ImGui::DragFloat2("Pos", editPos, 1.0f, -1000.0f, 1000.0f);
		ImGui::DragFloat2("Size", editSize, 1.0f, 1.0f, 1000.0f);

		objectI->get()->SetPos(editPos);
		objectI->get()->SetSize(editSize);


		if (ImGui::Button(std::string("erase" + num).c_str()))
		{
			//一つしかないなら
			if (StageManager::GetInstance()->stageObjData_.size() == 1)
			{
				//それしかないなら全部消す
				StageManager::GetInstance()->stageObjData_.clear();
				break;

			}
			else
			{
				objectI = StageManager::GetInstance()->stageObjData_.erase(objectI);
				continue;
			}
		}

		eventCount++;
		objectI++;
	}

	ImGui::End();
}

void EditStage::MouseEditObject()
{
	if (!isMouseObject_)
	{
		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (AABB(Input::GetMousePos(), objectI->get()))
			{
				if (Input::GetMouseKeyTrigger(Input::MouseKey::LEFT))
				{
					isMouseObject_ = true;
					oldObjPos_ = objectI->get()->GetPos();
					mouseEditObjPos = objectI->get()->GetPos();
					mouseMoveObject_ = objectI->get();
				}
				else
				{
					ImGui::Begin("Editor");
					ImGui::Text("edit: Leftclick");
					ImGui::End();
					
				}
			}
		}
	}
	else
	{
		mouseEditObjPos = Input::GetMousePos();

		ImGui::Begin("Editor");
		ImGui::Text("set:Leftclick\nUndo:SHIFT + Leftclick");
		ImGui::End();

		bool isSet = true;

		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (AABB(Input::GetMousePos(), mouseMoveObject_->GetSize(), objectI->get()) && mouseMoveObject_ != objectI->get())
			{
				isSet = false;
				mouseSetObjectColor = 0xff0000;
				break;
			}
		}

		if (isSet)
		{
			mouseSetObjectColor = 0xffffff;
		}

		if (Input::GetMouseKeyTrigger(Input::MouseKey::LEFT) && Input::GetKey(Input::Key::LShift))
		{
			mouseMoveObject_->SetPos(oldObjPos_);
			isMouseObject_ = false;
		}
		else if (Input::GetMouseKeyTrigger(Input::MouseKey::LEFT) && isSet)
		{
			mouseMoveObject_->SetPos(Input::GetMousePos());
			isMouseObject_ = false;
		}	
		
	}
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
		name = std::string("jsonObjectData");
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
		name = std::string("jsonObjectData");
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

void EditStage::CopyPasteMouseObject()
{
	if (isMouseObject_ && Input::GetKey(Input::Key::LControl) && Input::GetKeyTrigger(Input::Key::C))
	{
		copyObject_ = *mouseMoveObject_;
	}

	if (Input::GetKey(Input::Key::LControl) && Input::GetKeyTrigger(Input::Key::V))
	{
		StageManager::GetInstance()->AddObject(copyObject_.GetPos(), copyObject_.GetSize(), copyObject_.GetObjectType());
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

bool EditStage::AABB(Vector2 mousePos, Object* obj)
{
	//マウスの判定の大きさ
	Vector2 size = { 1,1 };

	if (mousePos.x + size.x / 2 >= obj->GetPos().x - obj->GetSize().x / 2 &&
		mousePos.x - size.x / 2 <= obj->GetPos().x + obj->GetSize().x / 2)
	{
		if (mousePos.y + size.y / 2 <= obj->GetPos().y - obj->GetSize().y / 2 ||
			mousePos.y - size.y / 2 >= obj->GetPos().y + obj->GetSize().y / 2)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool EditStage::AABB(Vector2 pos, Vector2 size, Object* obj)
{

	if (pos.x + size.x / 2 >= obj->GetPos().x - obj->GetSize().x / 2 &&
		pos.x - size.x / 2 <= obj->GetPos().x + obj->GetSize().x / 2)
	{
		if (pos.y + size.y / 2 <= obj->GetPos().y - obj->GetSize().y / 2 ||
			pos.y - size.y / 2 >= obj->GetPos().y + obj->GetSize().y / 2)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}