#pragma once
#include"Vector2.h"

enum class ObjectType
{
	PLAYER,
	FLOAT_BLOCK,
	NOT_FLOAT_BLOCK,
	NONE,
};

class Object
{

public:
	virtual void Initialize() {}

	virtual void Update() {}

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

	ObjectType GetObjectType() {
		return objectType_;
	}

protected:
	Vector2 pos_ = { 0,0 };

	Vector2 oldPos_ = { 0,0 };

	Vector2 size_ = {0,0};

	bool isCollision_ = true;

	bool isExclude_ = true;
	
	ObjectType objectType_;
};

