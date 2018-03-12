#include "Entity.h"

Entity::Entity(){
	physicsNode = new PhysicsNode();
}

Entity::Entity(PhysicsNode *p):
	physicsNode(p)
{
}

Entity::~Entity() {
	delete physicsNode;

	physicsNode = nullptr;
}

void Entity::setPhysicsNode(PhysicsNode *p) {
	physicsNode = p;
}

void Entity::lookAt(Entity *b) {
	physicsNode->setRotation(getAngle(b));
}

void Entity::moveTowards(Entity *b, float msec) {
	float rot = getAngle(b);
	rot *= PI / 180;
	Vector2 temp = Vector2(cos(rot), sin(rot));

	physicsNode->setVelocity(Vector2(temp.x * physicsNode->getMaxSpeed() * msec, temp.y * physicsNode->getMaxSpeed() * msec));
	physicsNode->updatePosition(physicsNode->getVelocity().x, physicsNode->getVelocity().y);
}

void Entity::moveAway(Entity *b, float msec) {
	float rot = getAngle(b);
	rot *= PI / 180;
	Vector2 temp = Vector2(cos(rot), sin(rot));

	physicsNode->setVelocity(Vector2(-temp.x * physicsNode->getMaxSpeed() * msec, -temp.y * physicsNode->getMaxSpeed() * msec));
	physicsNode->updatePosition(physicsNode->getVelocity().x, physicsNode->getVelocity().y);
}

void Entity::moveForwards(float msec) {
	float rot = physicsNode->getRotation();
	rot *= PI / 180;
	Vector2 temp = Vector2(cos(rot), sin(rot));

	physicsNode->setVelocity(Vector2(temp.x * physicsNode->getMaxSpeed() * msec, temp.y * physicsNode->getMaxSpeed() * msec));
	physicsNode->updatePosition(physicsNode->getVelocity().x, physicsNode->getVelocity().y);
}

void Entity::moveBackwards(float msec) {
	float rot = physicsNode->getRotation();
	rot *= PI / 180;
	Vector2 temp = Vector2(cos(rot), sin(rot));

	physicsNode->setVelocity(Vector2(-temp.x * physicsNode->getMaxSpeed() * msec, -temp.y * physicsNode->getMaxSpeed() * msec));
	physicsNode->updatePosition(physicsNode->getVelocity().x, physicsNode->getVelocity().y);

}

void Entity::setHP(int hp) {
	hitPoints = hp;
}

void Entity::updateHP(int hp) {
	hitPoints += hp;
}

float Entity::getAngle(Entity *b) const {
	return atan2(
		b->getPhysicsNode()->getY() - physicsNode->getY(),
		b->getPhysicsNode()->getX() - physicsNode->getX())
		* (180 / PI);
}

float Entity::getDistanceSquared(Entity *b) const
{
	return 
		pow(physicsNode->getX() - b->getPhysicsNode()->getX(), 2) +
		pow(physicsNode->getY() - b->getPhysicsNode()->getY(), 2);
}

int Entity::getHP() const
{
	return hitPoints;
}

PhysicsNode* Entity::getPhysicsNode() {

	return physicsNode;
}
