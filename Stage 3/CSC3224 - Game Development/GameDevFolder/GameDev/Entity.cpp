#include "Entity.h"

Entity::Entity() 
{

}

Entity::~Entity() 
{

}

Vector2 Entity::getPosition() 
{
	return position;
}

Vector2 Entity::getVelocity()
{
	return velocity;
}

float Entity::getRotation() 
{
	return rotation;
}

float Entity::getDepth()
{
	return depth;
}

float Entity::getRadius()
{
	return radius;
}

void Entity::setPosition(Vector2 position) 
{
	this->position = position;
}

void Entity::updatePosition() 
{
	position.x += velocity.x;
	position.y += velocity.y;
}

void Entity::setVelocity(Vector2 velocity)
{
	this->velocity = velocity;
}

void Entity::updateVelocity(Vector2 velocity)
{
	this->velocity.x += velocity.x;
	this->velocity.y += velocity.y;
}

void Entity::setRotation(float rotation) {
	this->rotation = rotation;
}

void Entity::updateRotation(float rotation) {
	this->rotation += rotation;
}

void Entity::setDepth(float depth) {
	this->depth = depth;
}

void Entity::updateDepth(float depth) {
	this->depth += depth;
}

void Entity::setRadius(float radius)
{
	this->radius = radius;
}
