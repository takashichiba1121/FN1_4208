#include "Collision.h"

bool Collision::AABB(Object* objA, Object* objB)
{
	if (objA->GetPos().x + objA->GetSize().x/2 >= objB->GetPos().x - objB->GetSize().x/2 &&
		objA->GetPos().x - objA->GetSize().x/2 <= objB->GetPos().x + objB->GetSize().x/2)
	{
		if (objA->GetPos().y + objA->GetSize().y/2 <= objB->GetPos().y - objB->GetSize().y/2 ||
			objA->GetPos().y - objA->GetSize().y/2 >= objB->GetPos().y + objB->GetSize().y/2)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}
