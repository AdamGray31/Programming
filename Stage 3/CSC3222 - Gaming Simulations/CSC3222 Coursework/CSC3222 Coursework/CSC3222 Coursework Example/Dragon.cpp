#include "Dragon.h"

Dragon::Dragon() {
	Entity::setHP(1000);
	target = nullptr;
}

Dragon::Dragon(PhysicsNode * p):
	Entity(p)
{
	Entity::setHP(1000);
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
