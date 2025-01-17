#include "EditStage.h"
#include "DxLib.h"
#include <fstream>

#include "Input.h"
#include "Water.h"
#include "CollisionManager.h"

#include "Player.h"
#include "Block.h"
#include "Goal.h"
#include "levitationBlock.h"
#include "BreakBlock.h"
#include "Water.h"
#include "Window.h"
#include "Key.h"
#include "SpongeBlock.h"
#include "Drain.h"
#include "TutorialObject.h"
#include "Water.h"

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
#ifdef _DEBUG
	StageManager::GetInstance()->SetIsUseEditer(true);
#endif
}

void EditStage::Update()
{
	if (StageManager::GetInstance()->GetIsUseEditer())
	{
		EditorUpdate();
	}
	else
	{
		ImGui::Begin("test");

		if (ImGui::Button("testStop"))
		{
			TestEnd();
		}

		ImGui::End();
	}
}

void EditStage::Draw()
{
	if (!StageManager::GetInstance()->GetIsUseEditer())return;
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
	ImguiMenu();

	addObject();

	EditObject();

	CopyPasteMouseObject();

	Undo();
	Redo();
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

	horizontal_ = Water::GetInstance()->GetTentHorizontal();

	ImGui::DragFloat("horizontal", &horizontal_, 1.0f, 0.0f, 720);
	Water::GetInstance()->SetTentHorizontal(horizontal_);

	if (StageManager::GetInstance()->GetIsUseEditer() && StageManager::GetInstance()->stageObjData_.size() != 0)
	{
		if (ImGui::Button("TestStart"))
		{	
			TestStart();
		}
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
		serectAddObjectType_ = ObjectName::ObjectString<ObjectType>(objectType);
	}

	for (size_t i = 0; i < items.size(); i++)
	{
		if (ImGui::Button(items[i].c_str(), {50,50}))
		{
			serectAddObjectType_ = ObjectName::ObjectString<ObjectType>(i);
		}
		if (i != 0 && i % 4 == 0)
		{
			continue;
		}

		if (i != items.size()-1)
		{
			ImGui::SameLine();
		}
		
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
		UndoStack(EditContent::Content::Add);
	}

	if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) && Input::GetMouseKeyTrigger(Input::MouseKey::RIGHT))
	{
		StageManager::GetInstance()->AddObject(Input::GetMousePos(), AddObjectSize_, serectAddObjectType_);
		UndoStack(EditContent::Content::Add);
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
		ImGui::Combo(std::string("object Type" + num).c_str(), objectType, items);

		if (oldObjectType != objectType)
		{
			EditContent::TicketData changeTagData;
			changeTagData.type_ = ObjectName::ObjectString<ObjectType>(objectType);
			changeTagData.oldType_ = ObjectName::ObjectString<ObjectType>(oldObjectType);
			UndoStack(EditContent::Content::ChangeTag, changeTagData, eventCount);
			StageManager::GetInstance()->ChengeTag(objectI, ObjectName::ObjectString<ObjectType>(objectType));
		}

		if (Input::GetMouseKeyTrigger(Input::MouseKey::LEFT))
		{
			movedata_.setData(objectI->get()->Clone(), objectI->get()->GetPos(), objectI->get()->GetSize());
		}

		Vector2 editPos = objectI->get()->GetPos();
		Vector2 editSize = objectI->get()->GetSize();

		if (ImGui::DragFloat2(std::string("Pos" + num).c_str(), editPos, 1.0f, -1000.0f, 1000.0f) && Input::GetMouseKey(Input::MouseKey::LEFT))isImguiUse_ = true;
		if (ImGui::DragFloat2(std::string("Size" + num).c_str(), editSize, 1.0f, 1.0f, 1000.0f) && Input::GetMouseKey(Input::MouseKey::LEFT))isImguiUse_ = true;

		objectI->get()->SetPos(editPos);
		objectI->get()->SetSize(editSize);

		if (isImguiUse_ && !Input::GetMouseKey(Input::MouseKey::LEFT))
		{
			UndoStack(EditContent::Content::Move, movedata_, eventCount);
			isImguiUse_ = false;
		}

		if (ImGui::TreeNode(std::string("seting" + num).c_str()))
		{
			objectI->get()->ImGuiEdit();
			ImGui::TreePop();
		}


		if (ImGui::Button(std::string("erase" + num).c_str()))
		{
			EditContent::TicketData data;
			data.setData(objectI->get()->Clone());
			UndoStack(EditContent::Content::Delete,data, eventCount);

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
		int32_t objectCount = 0;
		for (auto objectI = StageManager::GetInstance()->stageObjData_.begin(); objectI != StageManager::GetInstance()->stageObjData_.end(); objectI++)
		{
			if (AABB(Input::GetMousePos(), objectI->get()) && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
			{
				if (Input::GetMouseKeyTrigger(Input::MouseKey::LEFT))
				{
					isMouseObject_ = true;
					oldObjPos_ = objectI->get()->GetPos();
					mouseEditObjPos = objectI->get()->GetPos();
					mouseMoveObject_ = objectI->get();
					mouseMoveObjectUndoObjectNum_ = objectCount;

				}
				else
				{
					ImGui::Begin("Editor");
					ImGui::Text("edit: Leftclick");
					ImGui::End();
					
				}
			}
			objectCount++;
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
		else if (Input::GetMouseKeyTrigger(Input::MouseKey::LEFT) && isSet && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
		{
			EditContent::TicketData data;
			data.setData(mouseMoveObject_->Clone(), mouseMoveObject_->GetPos(), mouseMoveObject_->GetSize());
			mouseMoveObject_->SetPos(Input::GetMousePos());
			UndoStack(EditContent::Content::Move,data,mouseMoveObjectUndoObjectNum_);
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
	jsonfile["LevelName"] = LevelName_.c_str();

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
	jsonfile["LevelName"] = LevelName_.c_str();

	//水面の高さ
	jsonfile["horizontal"] = horizontal_;

	for (auto& levelData : StageManager::GetInstance()->stageObjData_)
	{
		nlohmann::json data;

		//objectという固まりの中に情報を入れる
		data["object"]["pos"] = { levelData->GetPos().x,levelData->GetPos().y };
		data["object"]["scale"] = { levelData->GetSize().x,levelData->GetSize().y };
		data["object"]["tag"] = static_cast<int32_t>(levelData->GetObjectType());

		levelData->SetJson(data["object"]["IndividualSettings"]);

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
		SaveAndSetLevelName();
		
	}
	if (imguiLoadWindow_)
	{
		loadData = ImportLevel::GetInstance()->WindowsOpenLevelFile();
		if (loadData.isLoad)
		{
			//次に引き継がないデータを消しておく
			mouseMoveObject_ = nullptr;
			undoTickets_.clear();
			redoTickets_.clear();
			StageManager::GetInstance()->LoadListStageData(loadData.levelData);
			horizontal_ = loadData.horizontal;
			Water::GetInstance()->SetHorizontal(loadData.horizontal);
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

void EditStage::Undo()
{
	if (undoTickets_.empty())return;

	if (Input::GetKey(Input::Key::LControl) && Input::GetKeyTrigger(Input::Key::Z))
	{
		undoTickets_.back()->Undo();
		redoTickets_.push_back(std::move(undoTickets_.back()));
		undoTickets_.pop_back();
	}


}

void EditStage::Redo()
{
	if (redoTickets_.empty())return;

	if (Input::GetKey(Input::Key::LControl) && Input::GetKeyTrigger(Input::Key::Y))
	{
		redoTickets_.back()->Redo();
		undoTickets_.push_back(std::move(redoTickets_.back()));
		redoTickets_.pop_back();
	}
}

void EditStage::UndoStack(EditContent::Content content, EditContent::TicketData object, int32_t objectNum)
{
	std::unique_ptr<EditorTicket> addTicket;
	EditContent::DeleteObject ticket;
	EditContent::MoveTransform Moveticket;
	EditContent::ChangeObjectType ChangeTypeticket;
	//タグの内容で決定
	switch (content)
	{
	case EditContent::Content::Add:

		addTicket = std::make_unique<EditContent::AddObject>();
		addTicket->SaveData();
		undoTickets_.push_back(std::move(addTicket));

		break;

	case EditContent::Content::Delete:
		ticket.SaveData(object.object.get(), objectNum);

		addTicket = std::make_unique<EditContent::DeleteObject>(ticket);
		undoTickets_.push_back(std::move(addTicket));
		
		break;

	case EditContent::Content::Move:	
		Moveticket.SaveData(object, objectNum);

		addTicket = std::make_unique<EditContent::MoveTransform>(Moveticket);
		undoTickets_.push_back(std::move(addTicket));
		break;
	case EditContent::Content::ChangeTag:
		
		ChangeTypeticket.SaveData(object.type_, object.oldType_, objectNum);

		addTicket = std::make_unique<EditContent::ChangeObjectType>(ChangeTypeticket);
		undoTickets_.push_back(std::move(addTicket));
		break;
		break;
	default:
		break;
	}

	redoTickets_.clear();

}

std::string EditStage::ObjectTypeToString(ObjectType objectType)
{
	switch (objectType) {
	case ObjectType::PLAYER:   return "player";
	case ObjectType::SPONGE_BLOCK:   return "spongeBlock";
	case ObjectType::FLOAT_BLOCK: return "floatBlock";
	case ObjectType::NOT_FLOAT_BLOCK: return "notFloatBlock";
	case ObjectType::BREAK_BLOCK: return "breakBlock";
	case ObjectType::GOAL: return "goal";
	case ObjectType::KEY: return "key";
	case ObjectType::DRAIN: return "drain";
	case ObjectType::TUTORIAL: return "tutorial";
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

void EditStage::TestStart()
{
	StageManager::GetInstance()->SetIsUseEditer(false);
	

	for (auto& object : StageManager::GetInstance()->stageObjData_)
	{
		testSaveObject_.push_back(std::move(object->Clone()));
	}
}

void EditStage::TestEnd()
{
	StageManager::GetInstance()->SetIsUseEditer(true);
	/*std::list<Object>::iterator saveObject = testSaveObject_.begin();
	for (auto& object : StageManager::GetInstance()->stageObjData_)
	{
		object->SetCollision(saveObject->IsCollision());
		object->SetExclude(saveObject->IsExclude());
		object->SetObjectType(saveObject->GetObjectType());
		object->SetPos(saveObject->GetPos());
		object->SetSize(saveObject->GetSize());
		saveObject++;
	}*/

	StageManager::GetInstance()->stageObjData_.clear();
	StageManager::GetInstance()->SetKeyNum(0);
	CollisionManager::GetInstance()->AllDelete();
	std::unique_ptr<Object> addObj;

	for (auto& object : testSaveObject_)
	{
		if (object->GetObjectType() == ObjectType::KEY)
		{
			StageManager::GetInstance()->AddKeyNum();
		}
		addObj= std::move(object);
		addObj->Initialize();
		StageManager::GetInstance()->stageObjData_.push_back(std::move(addObj));
	}

	testSaveObject_.clear();
}

void EditStage::SaveAndSetLevelName()
{
	
	//ImGui::ShowDemoWindow();

	ImGui::Begin("LevelNameSet");

	ImGui::InputTextWithHint("input text","LevelName", str1, IM_ARRAYSIZE(str1));

	LevelName_ = std::string(str1);

	if (ImGui::Button("ok"))
	{
		WindowsSaveFile();
		imguiSaveWindow_ = false;
	}
	ImGui::End();
}
