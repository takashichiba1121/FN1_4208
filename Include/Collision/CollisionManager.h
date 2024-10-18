#pragma once
#include<list>
#include"Object.h"
class CollisionManager
{
public:

	void AddObject(Object* object);
	void RemoveObject(Object* object);

	void Update();

	static CollisionManager* GetInstance();
private:

	std::list<Object*>objects_;

};

