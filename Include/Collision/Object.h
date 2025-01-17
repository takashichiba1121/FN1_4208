#pragma once
#include"Vector2.h"
#include"Window.h"
#include"json.hpp"

enum class ObjectType
{
	PLAYER,
	SPONGE_BLOCK,
	FLOAT_BLOCK,
	NOT_FLOAT_BLOCK,
	BREAK_BLOCK,
	GOAL,
	KEY,
	DRAIN,
	TUTORIAL,
	NONE,
};

class Object
{

public:
	virtual void Initialize() {}

	virtual void Update() {}

	void ObjectUpdate();

	virtual void Inversion(const float easing) {}

	virtual void Draw() {}

	virtual void OnCollision(Object* object) {};

	void ObjectOnCollision(Object* object);

	virtual std::unique_ptr<Object> Clone() { return nullptr; };

	void SetCollision(bool isCollision) {
		isCollision_ = isCollision;
	}

	void SetExclude(bool isExclude) {
		isExclude_ = isExclude;
	}

	bool IsCollision() {
		return isCollision_;
	}

	bool IsExclude() {
		return isExclude_;
	}

	void SetPos(Vector2 pos) {
		pos_ = pos;
	}

	void SetTent() {
		easeSPos_ = pos_.y;
		easeEPos_ = WIN_HEIGHT / 2 + (WIN_HEIGHT / 2 - pos_.y);
		tentSize_ = size_.y;
	}

	 void SetSize(Vector2 size) {
		size_ = size;
	}

	void SetObjectType(ObjectType objectType) {
		objectType_ = objectType;
	}

	Vector2 GetPos() {
		return pos_;
	}

	Vector2 GetOldPos() {
		return oldPos_;
	}

	Vector2 GetSize() {
		return size_;
	}

	Vector2 GetOldSize() {
		return oldSize_;
	}

	ObjectType GetObjectType() {
		return objectType_;
	}

	virtual void SetJson(nlohmann::json& Level){};

	virtual void GetJson(nlohmann::json& Level) {};

	virtual void ImGuiEdit() {};

protected:
	Vector2 pos_ = { 0,0 };

	float easeSPos_ = pos_.y;
	float easeEPos_ = pos_.y;

	Vector2 oldPos_ = { 0,0 };

	Vector2 size_ = {1,1};

	Vector2 oldSize_ = { 0,0 };

	float tentSize_ = size_.y;

	bool isCollision_ = true;

	bool isExclude_ = true;
	
	ObjectType objectType_;
};

