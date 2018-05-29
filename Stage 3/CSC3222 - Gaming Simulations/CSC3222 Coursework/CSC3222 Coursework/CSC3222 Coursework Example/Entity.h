#pragma once
#include <vector>
#include "PhysicsNode.h"
#include "Node.h"
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
	void setMass(float m);
	void setHP(float hp);
	void updateHP(float hp);
	void setMaxHP(float hp);
	void pathTo(Node* startNode, Node* goalNode);
	float getAngle(Entity *b) const;
	float getDistanceSquared(Entity * b) const;
	float getMass() const;
	float getHP() const;
	float getMaxHP() const;
	bool isAlive() const;

	PhysicsNode* getPhysicsNode();

private:
	PhysicsNode* physicsNode;
	float mass;
	float hitPoints;
	float maxHP;

	

};