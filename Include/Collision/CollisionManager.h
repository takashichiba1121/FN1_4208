#pragma once
#include<list>
#include"Object.h"
class CollisionManager
{
public:

private:
	static CollisionManager* GetInstance();

	std::list<Object*>objects_;

};

