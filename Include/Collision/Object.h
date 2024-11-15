#pragma once
#include"Vector2.h"
#include"Window.h"

enum class ObjectType
{
	PLAYER,
	FLOAT_BLOCK,
	NOT_FLOAT_BLOCK,
	BREAK_BLOCK,
	GOAL,
	KEY,
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

	virtual void OnCollision(Object* objct) {};

	void ObjectOnCollision(Object* objct);

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

