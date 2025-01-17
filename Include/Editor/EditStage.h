#pragma once
#include "StageManager.h"
#include <imgui.h>
#include "EditorTicket.h"

/*
�V����objectType��ǉ����ăG�f�B�^�ɒǉ��������ꍇ
�ύX�ӏ�
�EEditStage.cpp�ɂ��� ObjectTypeToString�̒��g�ɒǉ�
�EstageManager.cpp���ɂ��� SelectObject�̒��g�ɒǉ�
�ELevelPreView.cpp���ɂ��� AddObject���ύX���Ă����Ɗ�����
*/

namespace ImGui
{
#include "vector"
	bool DragFloat2(const char* label, Vector2& v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	bool Combo(const std::string& comboName, int32_t& number, std::vector<std::string> items);
}

class EditStage
{
public:
	EditStage();
	~EditStage();

	void Initialize();

	void Update();

	void Draw();

private:

	void WindowsSaveFile(const std::vector<Object*>& saveData);
	void WindowsSaveFile();

	void SaveLevelFullPathData(const std::string& fileName, const std::vector<Object*>& saveData);
	void SaveLevelFullPathData(const std::string& fileName);

	//�G�f�B�^�p�̍X�V
	void EditorUpdate();

	//imgui�̃��j���[
	void ImguiMenu();

	//�I�u�W�F�N�g�ǉ�
	void addObject();

	//�I�u�W�F�N�g�ҏW
	void EditObject();

	//�}�E�X�ŃI�u�W�F�N�g��ҏW������
	void MouseEditObject();

	//�������Ă��R�s�[�ƃy�[�X�g
	void CopyPasteMouseObject();

	//�z�u�f�[�^�̕ۑ��Ɠǂݍ���
	void SaveAndLoadLevelObject();

	void Undo();
	void Redo();

	/// <summary>
	/// undo�̃X�^�b�N�ɒǉ�����
	/// </summary>
	/// <param name="content">�ύX�̎��</param>
	/// <param name="object">�ύX�̂������I�u�W�F�N�g</param>
	/// <param name="objectNum">�ύX�����ʒu(��ނɂ���Ă͕K�v�Ȃ�)</param>
	void UndoStack(EditContent::Content content, EditContent::TicketData object = {}, int32_t objectNum = 0);

	//objectType��n���ƃX�g�����O�ŕԂ��Ă����
	std::string ObjectTypeToString(ObjectType objectType);

	//������Ȃ̂Ől�̂�R�s�y
	bool AABB(Vector2 mousePos, Object* obj);
	bool AABB(Vector2 pos,Vector2 size, Object* obj);

	//�e�X�g�X�^�[�g�p�̏���
	void TestStart();

	//�e�X�g���I����Ƃ��̌㏈��
	void TestEnd();

	//�ۑ����̖��O�Z�b�g�p�̊֐�
	void SaveAndSetLevelName();


private:

	ObjectType serectAddObjectType_= ObjectType::NONE;

	Vector2 AddObjectPos_ = { 1,1 };
	Vector2 AddObjectSize_ = { 1,1 };

	InputLevelData loadData;

	bool imguiSaveWindow_ = false;
	bool imguiLoadWindow_ = false;
	bool imguiAddObjectWindow_ = false;

	//�}�E�X���I�u�W�F�N�g�������Ă��邩
	bool isMouseObject_ = false;

	bool isAddObjectDraw = false;

	int32_t addObjectColor = 0xffffff;
	int32_t mouseSetObjectColor = 0xffffff;

	//�}�E�X�ŃI�u�W�F�N�g���ړ�����ۂ̌��̈ʒu�ێ��p
	Vector2 oldObjPos_ = {};

	//�}�E�X�ŃI�u�W�F�N�g���ړ�����ۂ̈ړ���
	Vector2 mouseEditObjPos = {};

	Object* mouseMoveObject_ = nullptr;

	Object copyObject_;

	//�������̈ʒu
	float horizontal_ = 160.0f;

	float startHorizontal_ = 0.0f;

	std::vector<std::unique_ptr<EditorTicket>> undoTickets_;
	std::vector<std::unique_ptr<EditorTicket>> redoTickets_;

	//�e�X�g�p�̌��̈ʒu�ێ��plist
	std::list< std::unique_ptr<Object>> testSaveObject_;

	bool isImguiUse_ = false;

	EditContent::TicketData movedata_;

	int32_t mouseMoveObjectUndoObjectNum_ = 0;

	//�X�e�[�W�Z���N�g�ŕ`��p�̕���
	std::string LevelName_ = "";

	char str1[128] = "";
};

