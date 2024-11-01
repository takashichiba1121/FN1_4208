#pragma once
#include<list>
#include"Object.h"
class CollisionManager
{
#pragma region Singleton
private:
	CollisionManager() {};

	~CollisionManager() {};
public:
	CollisionManager(const CollisionManager& carManager) = delete;

	CollisionManager& operator=(const CollisionManager& carManager) = delete;

	static CollisionManager* GetInstance();
#pragma endregion
public:

	void AddObject(Object* object);
	void RemoveObject(Object* object);

	void Update();

	void AllDelete();
private:

	std::list<Object*>objects_;

};

