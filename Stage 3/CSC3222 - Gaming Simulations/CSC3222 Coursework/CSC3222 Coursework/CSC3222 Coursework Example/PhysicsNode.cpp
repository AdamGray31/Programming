#include "PhysicsNode.h"

PhysicsNode::PhysicsNode():
	position(Vector3(0.0f, 0.0f, 0.0f)), rotation(0.0f), radius(0.0f), aggroRange(0.0f), entitiesInRange(0), scale(Vector3(1.0f, 1.0f, 1.0f)) 
{

}

PhysicsNode::PhysicsNode(Vector3 position, float rotation, float radius, float aggroRange, Vector3 scale): 
	position(position), rotation(rotation), radius(radius), aggroRange(aggroRange), entitiesInRange(0), scale(scale) 
{

}

PhysicsNode::PhysicsNode(int x, int y, float rotation, float radius, float aggroRange, Vector3 scale):
	position(gridToFloat(x, y)), rotation(rotation), radius(radius), aggroRange(aggroRange), entitiesInRange(0), scale(scale)
{

}

PhysicsNode::PhysicsNode(PhysicsNode &p):
	position(p.getPosition()), rotation(p.getRotation()), radius(p.getRadius()), aggroRange(p.getAggroRange()), entitiesInRange(0), scale(p.getScale())
{
	
}

PhysicsNode::~PhysicsNode() 
{
}

void PhysicsNode::updateX(float x) 
{
	position.x += x;
}

void PhysicsNode::updateY(float y) 
{
	position.y += y;
}

void PhysicsNode::updatePosition(float x, float y) 
{
	position.x += x;
	position.y += y;
}

void PhysicsNode::updatePosition(Vector2 v, float msec) 
{
	
	v.Normalise();

	v *= currentSpeed;

	v *= msec;

	position.x += v.x;
	position.y += v.y;
}

void PhysicsNode::setPosition(Vector3 pos) 
{
	position = pos;
}

void PhysicsNode::setPosition(int x, int y) 
{
	position = gridToFloat(x, y);
}

void PhysicsNode::updateRotation(float r) 
{
	rotation += r;
}

void PhysicsNode::setRotation(float r) 
{
	rotation = r;
}

void PhysicsNode::updateAggroRange(float x) 
{
	aggroRange = x;
}

void PhysicsNode::setEntitiesInRange(int e) 
{
	entitiesInRange = e;
}

void PhysicsNode::setXScale(float x) 
{
	scale.x = x;
}

void PhysicsNode::setYScale(float y) 
{
	scale.y = y;
}

void PhysicsNode::updateXScale(float x) 
{
	scale.x += x;
}

void PhysicsNode::updateYScale(float y) 
{
	scale.y += y;
}

void PhysicsNode::updateScale(Vector3 s) 
{
	scale.x += s.x;
	scale.y += s.y;
}

void PhysicsNode::setRadius(float r) 
{
	radius = r;
}

void PhysicsNode::updateRadius(float r) 
{
	radius += r;
}

void PhysicsNode::setVelocity(Vector2 v) 
{
	velocity = v;
}

void PhysicsNode::setMaxSpeed(float v) 
{
	maxSpeed = v;
}

void PhysicsNode::setCurrentSpeed(float v)
{
	currentSpeed = v;
}

float PhysicsNode::getX() const 
{
	return position.x;
}

float PhysicsNode::getY() const 
{
	return position.y;
}

Vector3 PhysicsNode::getPosition() const 
{
	return position;
}

float PhysicsNode::getRotation() const 
{
	return rotation;
}

float PhysicsNode::getAggroRange() const 
{
	return aggroRange;
}

int PhysicsNode::getEntitiesInRange() const 
{
	return entitiesInRange;
}

float PhysicsNode::getXScale() const 
{
	return scale.x;
}

float PhysicsNode::getYScale() const 
{
	return scale.y;
}

Vector3 PhysicsNode::getScale() const 
{
	return scale;
}

float PhysicsNode::getRadius() const 
{
	return radius;
}

Vector2 PhysicsNode::getVelocity() const 
{
	return velocity;
}

float PhysicsNode::getMaxSpeed() const 
{
	return maxSpeed;
}

float PhysicsNode::getCurrentSpeed() const
{
	return currentSpeed;
}

Vector3 PhysicsNode::gridToFloat(int x, int y) 
{
	return Vector3(x * 26.66f + 12.0f, y * 26.66f - 2.0f, position.z);
}
