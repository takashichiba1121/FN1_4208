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
				if (!objectA->IsExclude()||!objectB->IsExclude())
				{
					Vector2 posB = objectB->GetPos();
					Vector2 sizeB = objectB->GetSize();
					Vector2 oldPosB = objectB->GetOldPos();

					Vector2 posA = objectA->GetPos();
					Vector2 sizeA = objectA->GetSize();
					Vector2 oldPosA = objectA->GetOldPos();

					if (objectA->GetObjectType() < objectB->GetObjectType())
					{
						if (posB.y - sizeB.y >= oldPosA.y + sizeA.y)
						{
							posA.y = posB.y - (sizeB.y + sizeA.y);
						}
						else if (posB.y + sizeB.y <= oldPosA.y - sizeA.y)
						{
							posA.y = posB.y + sizeB.y + sizeA.y;
						}
						else
						{

							if (posB.x + sizeB.x <= oldPosA.x - sizeB.x)
							{
								posA.x = posB.x + sizeB.x + sizeA.x + 0.1f;
							}
							else if (posB.x - sizeB.x >= oldPosA.x + sizeA.x)
							{
								posA.x = posB.x - (sizeB.x + sizeA.x) - 0.1f;

							}
						}
						objectA->SetPos(posA);
					}
					else
					{

						if (posA.y - sizeA.y >= oldPosB.y + sizeB.y)
						{
							posB.y = posA.y - (sizeA.y + sizeB.y);
						}
						else if (posA.y + sizeA.y <= oldPosB.y - sizeB.y)
						{
							posB.y = posA.y + sizeA.y + sizeB.y;
						}
						else
						{

							if (posA.x + sizeA.x <= oldPosB.x - sizeA.x)
							{
								posB.x = posA.x + sizeA.x + sizeB.x + 0.1f;
							}
							else if (posA.x - sizeA.x >= oldPosB.x + sizeB.x)
							{
								posB.x = posA.x - (sizeA.x + sizeB.x) - 0.1f;

							}
						}
					}

						objectB->SetPos(posB);
				}

				objectA->OnCollision(objectB);
				objectB->OnCollision(objectA);

			}
		}
	}

}

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}
