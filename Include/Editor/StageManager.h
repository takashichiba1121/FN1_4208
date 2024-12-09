#pragma once
#include "DxLib.h"
#include "Object.h"
#include "ImportLevel.h"
#include <vector>
#include <memory>
#include <list>
#include <sstream>

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

	void ChengeTag(const std::list<std::unique_ptr<Object>>::iterator& chengeData, ObjectType tag);

	std::list<std::unique_ptr<Object>> stageObjData_;

	bool GetIsUseEditer() { return isUseEditer_; };

	void SetIsUseEditer(bool flag) { isUseEditer_ = flag; };

	size_t GetStageFileNameNum() { return stageFileName_.size(); };

	int32_t GetNowLevelNum() { return nowLevelNum_; };

	void SelectLevelNum(int32_t selectNum);

	void NextLevelLoad();

	std::string GetStageFileName(int32_t num) { return stageFileName_[num]; };

	//���̐����擾
	int32_t GetKeyNum() { return KeyNum_; };

	//�����擾�����̂Ō��̐������炷�֐�
	void GetKey() { KeyNum_--; };

private:

	//�V���O���g���p
	StageManager() = default;
	~StageManager();

	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;

	std::unique_ptr<Object> SelectObject(ObjectType tag);


private:

	//�X�e�[�W�Ƃ��Ēǉ��������t�@�C������ێ�
	std::vector<std::string> stageFileName_;

	uint32_t nowLevelNum_ = 0;
	
	bool isUseEditer_ = false;

	int32_t KeyNum_ = 0;

	bool isClear_ = false;
};

