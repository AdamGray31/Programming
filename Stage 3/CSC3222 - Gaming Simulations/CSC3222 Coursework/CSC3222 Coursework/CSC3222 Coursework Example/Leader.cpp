#include "Leader.h"

Leader::Leader()
{
	Entity::setHP(200);
	Entity::setMaxHP(200);
	Entity::setMass(10.0f);
}

Leader::Leader(PhysicsNode *p) :
	Entity(p)
{
	Entity::setHP(200);
	Entity::setMaxHP(200);
	Entity::setMass(10.0f);		
}


Leader::~Leader()
{
}
