#pragma once
#include"Vector2.h"

enum class ObjectType
{
	PLAYER,
	FLOAT_BLOCK,
};

class Object
{

public:
	virtual void Initialize() {}

	virtual void Update() {}

	virtual void Draw() {}

	virtual void OnCollision(Object objct) {};

	void ObjectOnCollision(Object objct);

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
		pos_= pos;
	}

	void SetSize(Vector2 size) {
		size_ = size;
	}

	Vector2 GetPos() {
		return pos_;
	}

	Vector2 GetSize() {
		return size_;
	}

protected:
	Vector2 pos_;

	Vector2 size_;

	bool isCollision_ = true;

	bool isExclude_ = true;
	
	ObjectType objectType;
};

