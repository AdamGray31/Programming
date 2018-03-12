#pragma once
#include "Entity.h"
class Follower :
	public Entity
{
public:
	Follower();
	Follower(PhysicsNode *p);
	~Follower();
};

