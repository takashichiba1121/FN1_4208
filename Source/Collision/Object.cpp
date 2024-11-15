#include "Object.h"

void Object::ObjectUpdate()
{
	oldPos_ = pos_;

	oldSize_ = size_;
}

void Object::ObjectOnCollision(Object* objct)
{
}
