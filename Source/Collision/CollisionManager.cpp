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
					Vector2 oldSizeB = objectB->GetOldSize();
					Vector2 oldPosB = objectB->GetOldPos();

					Vector2 posA = objectA->GetPos();
					Vector2 sizeA = objectA->GetSize();
					Vector2 oldSizeA = objectA->GetOldSize();
					Vector2 oldPosA = objectA->GetOldPos();

					Vector2 move = { 0,0 };

					Vector2 oldMove = { 0,0 };



					if (posA.y < posB.y)
					{
						move.y = (posB.y - sizeB.y / 2)-(posA.y + sizeA.y / 2);

						oldMove.y = (oldPosB.y - oldSizeB.y / 2) -(oldPosA.y + oldSizeA.y / 2);
					}
					else
					{
						move.y = (posA.y - sizeA.y / 2) - (posB.y + sizeB.y / 2);

						oldMove.y = (oldPosA.y - oldSizeA.y / 2) - (oldPosB.y + oldSizeB.y / 2);
					}

					if (posA.x < posB.x)
					{
						move.x = (posA.x + sizeA.x / 2)- (posB.x - sizeB.x / 2);

						oldMove.x = (oldPosA.x + oldSizeA.x / 2)- (oldPosB.x - oldSizeB.x / 2);
					}
					else
					{
						move.x = (posA.x - sizeA.x / 2) - (posB.x + sizeB.x / 2);

						oldMove.x = (oldPosA.x - oldSizeA.x / 2) - (oldPosB.x + oldSizeB.x / 2);
					}

					if (move.x > 0 && oldMove.x > 0 || move.x < 0 && oldMove.x < 0)
					{
						move.x = 0;

						oldMove.x = 0;
					}
					if (move.y > 0 && oldMove.y > 0 || move.y < 0 && oldMove.y < 0)
					{
						move.y = 0;

						oldMove.y = 0;
					}

					if (objectA->GetObjectType() < objectB->GetObjectType())
					{

						posA += move;

						objectA->SetPos(posA);
					}
					else
					{

						posB += move;

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
