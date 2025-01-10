#pragma once
#include "DxLib.h"
#include "Object.h"
#include "ImportLevel.h"
#include <vector>
#include <memory>
#include <list>
#include <sstream>
#include "ConfettiEmiitter.h"

class StageManager
{
public:
	//�������̓V���O���g������
	static StageManager* GetInstance();

	//std::vector<Object> LoadStageData(const std::string& fileName);
	void LoadListStageData(std::list<LevelData> levelData);

	void LoadStageObjectFile(const std::string& fileName);

	void Initialize();

	void Update();

	void Inversion(const float easing);

	void SetTentPos();

	void Draw();

	void AddObject(Vector2 pos, Vector2 size, ObjectType tag);
	void AddObject(Vector2 pos, Vector2 size, ObjectType tag, nlohmann::json seting);

	void ChengeTag(const std::list<std::shared_ptr<Object>>::iterator& chengeData, ObjectType tag);

	std::list<std::shared_ptr<Object>> stageObjData_;

	bool GetIsUseEditer() { return isUseEditer_; };

	void SetIsUseEditer(bool flag) { isUseEditer_ = flag; };

	int32_t GetStageFileNameNum() { return stageFileName_.size(); };

	int32_t GetNowLevelNum() { return nowLevelNum_; };

	void SelectLevelNum(int32_t selectNum);

	void NextLevelLoad();

	bool GetIsClear() { return isClear_; };

	void SetIsClear(bool flag) { isClear_ = flag; };

	std::string GetStageFileName(int32_t num) { return stageFileName_[num]; };

	//���̐����擾
	int32_t GetKeyNum() { return KeyNum_; };

	//�����擾�����̂Ō��̐������炷�֐�
	void GetKey() { KeyNum_--; };

	//�ǂݍ��݂Ȃ������Ƃ����̒ǉ����������Ƃ��̊֐�
	void AddKeyNum() { KeyNum_++; };

	//���̐��̎w�肪�������Ƃ��̊֐�
	void SetKeyNum(int32_t num) { KeyNum_ = num; };

	/// <summary>
	/// ���ǂ����邩�����肷��
	/// </summary>
	/// <param name="selectRetrun">false=���̃X�e�[�W��,true=�X�e�[�W�Z���N�g��</param>
	void NextSelect(bool selectReturn);

	//���ǂݍ���ł�X�e�[�W��ǂݍ��݂Ȃ���
	void NowStageReset();

	//�e�X�g���̃I�u�W�F�N�g�ێ��p
	std::shared_ptr<Object> TestSaveSelectObject(Object object);

	std::unique_ptr<Object> SelectObject(ObjectType tag);

private:

	//�V���O���g���p
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

	Vector2 GetGraphSize(int32_t GraphHandle);


private:

	//�G�~�b�^�[
	ConfettiEmiitter confettiEmitter;

	//�X�e�[�W�Ƃ��Ēǉ��������t�@�C������ێ�
	std::vector<std::string> stageFileName_;

	uint32_t nowLevelNum_ = 0;
	
	bool isUseEditer_ = false;

	int32_t KeyNum_ = 0;

	bool isClear_ = false;

	bool isNextLoad_ = false;

	float easingFrame_ = 0;
	float maxEasingFrame_ = 50;

	float clearTextSize_ = 0;

	uint32_t clearTextTextruehandle1_ = 0;
	uint32_t clearTextTextruehandle2_ = 0;
	uint32_t clearTextTextruehandle3_ = 0;
};

