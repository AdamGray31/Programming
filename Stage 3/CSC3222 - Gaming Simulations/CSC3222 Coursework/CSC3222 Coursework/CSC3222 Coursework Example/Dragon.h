#pragma once
#include "Entity.h"
class Dragon :
	public Entity
{
public:
	Dragon();
	Dragon(PhysicsNode *p);
	~Dragon();
	void setTarget(Entity *e);
	Entity* getTarget() const;
private:
	Entity *target;
};

