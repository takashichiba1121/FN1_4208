#pragma once
#include <string>
#include <list>
#include "Vector2.h"
#include "Object.h"
#include "ImportLevel.h"

struct PreViewData
{
	Vector2 pos_;
	Vector2 size_;

	ObjectType tag_ = ObjectType::NONE;

	uint32_t handle_ = 0;
	

};

class LevelPreView
{
public:
	LevelPreView();
	~LevelPreView();

	void Initialize(std::string selectFileName);

	void Update();

	void Draw();

	void ChengePreview(std::string selectFileName);

	Vector2 pos_;
	Vector2 size_ = {1,1};

private:

	void LoadStageObjectFile(const std::string& fileName);
	void LoadListStageData(std::list<LevelData> levelData);
	void AddObject(Vector2 pos, Vector2 size, ObjectType tag);

	Vector2 GetGraphSize(int32_t GraphHandle);

private:

	std::list<PreViewData> previewData_;

	float waterHorizontal_ = 0;

	std::string nowSelectfileName_ = "";

	bool lockDoor_ = false;

	uint32_t lockhandle_ = 0;

	float colA[4] = { 0.392f,1.0f,1.0f,0.274f };
	float colB[4] = { 0.5f,0.5f,1.0f,0.274f };

};

