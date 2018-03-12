#pragma once
#include "PhysicsNode.h"
#include "../../nclgl/common.h"

class Entity {
public:
	Entity();
	Entity(PhysicsNode *p);
	~Entity();
	void setPhysicsNode(PhysicsNode *p);
	void lookAt(Entity *b);
	void moveTowards(Entity *b, float msec);
	void moveAway(Entity *b, float msec);
	void moveForwards(float msec);
	void moveBackwards(float msec);
	void setHP(int hp);
	void updateHP(int hp);
	float getAngle(Entity *b) const;
	float getDistanceSquared(Entity * b) const;
	int getHP() const;
	PhysicsNode* getPhysicsNode();
private:
	PhysicsNode* physicsNode;
	int hitPoints;
};