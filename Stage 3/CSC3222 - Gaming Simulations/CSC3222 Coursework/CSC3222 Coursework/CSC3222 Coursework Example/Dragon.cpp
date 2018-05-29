#include "Dragon.h"

Dragon::Dragon() {
	Entity::setHP(1000);
	Entity::setMaxHP(1000);
	Entity::setMass(20.0f);
	target = nullptr;
}

Dragon::Dragon(PhysicsNode * p):
	Entity(p)
{
	Entity::setHP(1000);
	Entity::setMaxHP(1000);
	Entity::setMass(20.0f);
	target = nullptr;
}

Dragon::~Dragon() {
	delete target;
}

void Dragon::setTarget(Entity *e) {
	target = e;
}

Entity *Dragon::getTarget() const {
	return target;
}
