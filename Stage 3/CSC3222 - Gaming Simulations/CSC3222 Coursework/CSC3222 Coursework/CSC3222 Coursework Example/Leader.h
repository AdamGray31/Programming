#pragma once
#include "Entity.h"
class Leader :
	public Entity
{
public:
	Leader();
	Leader(PhysicsNode *p);
	~Leader();
};

