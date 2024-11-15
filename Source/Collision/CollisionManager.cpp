#include "CollisionManager.h"
#include"Collision.h"

void CollisionManager::AddObject(Object* object)
{
	objects_.push_front(object);
}

void CollisionManager::RemoveObject(Object* object)
{
	objects_.remove(object);
}

void CollisionManager::Update()
{
	auto itrA = objects_.begin();

	for (; itrA != objects_.end(); ++itrA)
	{
		Object* objectA = *itrA;

		if (!objectA->IsCollision())
		{
			continue;
		}

		auto itrB = itrA;
		itrB++;

		for (; itrB != objects_.end(); ++itrB)
		{
			Object* objectA = itrA._Ptr->_Myval;
			Object* objectB = itrB._Ptr->_Myval;

			if (!objectB->IsCollision())
			{
				continue;
			}

			if (Collision::AABB(objectA, objectB))
			{
				if (objectA->IsExclude() && objectB->IsExclude())
				{
					Vector2 posB = objectB->GetPos();
					Vector2 sizeB = objectB->GetSize();
					Vector2 oldPosB = objectB->GetOldPos();

					Vector2 posA = objectA->GetPos();
					Vector2 sizeA = objectA->GetSize();
					Vector2 oldPosA = objectA->GetOldPos();

					Vector2 moveA = { 0,0 };

					Vector2 moveB = { 0,0 };



					if (posA.y < posB.y)
					{
						moveA.y = (posA.y + sizeA.y / 2)- (posB.y - sizeB.y / 2);

						moveB.y = (oldPosA.y + sizeA.y / 2)- (oldPosB.y - sizeB.y / 2);
					}
					else
					{
						moveA.y = (posA.y - sizeA.y / 2) - (posB.y + sizeB.y / 2);

						moveB.y = (oldPosA.y - sizeA.y / 2) - (oldPosB.y + sizeB.y / 2);
					}

					if (posA.x < posB.x)
					{
						moveA.x = (posA.x + sizeA.x / 2)- (posB.x - sizeB.x / 2);

						moveB.x = (oldPosA.x + sizeA.x / 2)- (oldPosB.x - sizeB.x / 2);
					}
					else
					{
						moveA.x = (posA.x - sizeA.x / 2) - (posB.x + sizeB.x / 2);

						moveB.x = (oldPosA.x - sizeA.x / 2) - (oldPosB.x + sizeB.x / 2);
					}

					if (moveA.x > 0 && moveB.x > 0 || moveA.x < 0 && moveB.x < 0)
					{
						moveA.x = 0;

						moveB.x = 0;
					}
					if (moveA.y > 0 && moveB.y > 0 || moveA.y < 0 && moveB.y < 0)
					{
						moveA.y = 0;

						moveB.y = 0;
					}

					if (objectA->GetObjectType() < objectB->GetObjectType())
					{

						posA += moveA;

						objectA->SetPos(posA);
					}
					else
					{

						posB += moveA;

						objectB->SetPos(posB);
					}
				}

				objectA->OnCollision(objectB);
				objectB->OnCollision(objectA);

			}
		}
	}

}

void CollisionManager::AllDelete()
{
	objects_.clear();
}

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}
