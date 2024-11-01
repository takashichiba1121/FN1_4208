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
 				if (objectA->IsExclude()&&objectB->IsExclude())
				{
 					Vector2 posB = objectB->GetPos();
					Vector2 sizeB = objectB->GetSize();
					Vector2 oldPosB = objectB->GetOldPos();

					Vector2 posA = objectA->GetPos();
					Vector2 sizeA = objectA->GetSize();
					Vector2 oldPosA = objectA->GetOldPos();

					if (objectA->GetObjectType() < objectB->GetObjectType())
					{
						if (posB.y - sizeB.y/2 >= oldPosA.y + sizeA.y/2)
						{
							posA.y = posB.y - (sizeB.y/2 + sizeA.y/2);
						}
						else if (posB.y + sizeB.y/2 <= oldPosA.y - sizeA.y/2)
						{
							posA.y = posB.y + sizeB.y/2 + sizeA.y/2;
						}
						else
						{

							if (posB.x + sizeB.x/2 <= oldPosA.x - sizeA.x/2)
							{
								posA.x = posB.x + sizeB.x/2 + sizeA.x/2 + 0.1f;
							}
							else if (posB.x - sizeB.x/2 >= oldPosA.x + sizeA.x/2)
							{
								posA.x = posB.x - (sizeB.x/2 + sizeA.x/2) - 0.1f;

							}
						}
						objectA->SetPos(posA);
					}
					else
					{

						if (posA.y - sizeA.y/2 >= oldPosB.y + sizeB.y/2)
						{
							posB.y = posA.y - (sizeA.y/2 + sizeB.y/2);
						}
						else if (posA.y + sizeA.y/2 <= oldPosB.y - sizeB.y/2)
						{
							posB.y = posA.y + sizeA.y/2 + sizeB.y/2;
						}
						else
						{

							if (posA.x + sizeA.x/2 <= oldPosB.x - sizeB.x/2)
							{
								posB.x = posA.x + sizeA.x/2 + sizeB.x/2;
							}
							else if (posA.x - sizeA.x/2 >= oldPosB.x + sizeB.x/2)
							{
								posB.x = posA.x - (sizeA.x/2 + sizeB.x/2);

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

void CollisionManager::AllDelete()
{
	objects_.clear();
}

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}
