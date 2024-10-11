#include "Collision.h"

bool Collision::AABB(Object* objA, Object* objB)
{
	if (objA->GetPos().x + objA->GetSize().x >= objB->GetPos().x - objB->GetSize().x &&
		objA->GetPos().x - objA->GetSize().x <= objB->GetPos().x + objB->GetSize().x)
	{
		if (objA->GetPos().y + objA->GetSize().y <= objB->GetPos().y - objB->GetSize().y ||
			objA->GetPos().y - objA->GetSize().y >= objB->GetPos().y + objB->GetSize().y)
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
