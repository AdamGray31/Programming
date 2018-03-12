#include "Leader.h"

Leader::Leader()
{
	Entity::setHP(200);
}

Leader::Leader(PhysicsNode *p):
	Entity(p)
{
	Entity::setHP(200);
}


Leader::~Leader()
{
}
