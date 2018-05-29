#include "Follower.h"
#include <stdlib.h>

Follower::Follower() : 
	damage(10)
{
	Entity::setHP(rand() % 51 + 100);
	Entity::setMaxHP(150);
	Entity::setMass(10.0f);
}

Follower::Follower(PhysicsNode * p) :
	Entity(p), damage(10)
{
	Entity::setHP(rand() % 51 + 100);
	Entity::setMaxHP(150);
	Entity::setMass(10.0f);
}

Follower::~Follower() {

}

void Follower::changeDamage(int d)
{
	damage = d;
}

void Follower::setTask(bool doingTask, int t)
{
	this->doingTask = doingTask;
	this->currentTask = t;
}

int Follower::getDamage() const
{
	return damage;
}

bool Follower::isDoingTask() const
{
	return doingTask;
}

int Follower::getTask() const
{
	return currentTask;
}
