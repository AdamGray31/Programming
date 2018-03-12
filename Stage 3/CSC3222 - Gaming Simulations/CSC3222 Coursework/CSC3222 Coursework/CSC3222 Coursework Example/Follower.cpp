#include "Follower.h"
#include <stdlib.h>

Follower::Follower() {
	Entity::setHP(rand() % 51 + 100);
}

Follower::Follower(PhysicsNode * p):
	Entity(p)
{
	Entity::setHP(rand() % 51 + 100);
}


Follower::~Follower() {

}
