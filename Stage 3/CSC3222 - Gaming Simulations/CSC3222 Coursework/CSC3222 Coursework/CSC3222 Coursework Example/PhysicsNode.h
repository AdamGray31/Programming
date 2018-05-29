#pragma once
#include "../../nclgl/Vector3.h"
#include "../../nclgl/Vector2.h"

class PhysicsNode {
public:
	
	PhysicsNode();
	PhysicsNode(Vector3 position, float rotation, float radius, float aggroRange = 0, Vector3 scale = Vector3());
	PhysicsNode(int x, int y, float rotation, float radius, float aggroRange = 0, Vector3 scale = Vector3());
	PhysicsNode(PhysicsNode &p);
	~PhysicsNode();

	//Update private members
	void updateX(float x);
	void updateY(float y);
	void updatePosition(float x, float y);
	void updatePosition(Vector2 v, float msec);
	void setPosition(Vector3 pos);
	void setPosition(int x, int y);
	void updateRotation(float r);
	void setRotation(float r);
	void updateAggroRange(float x);
	void setEntitiesInRange(int e);
	void setXScale(float x);
	void setYScale(float y);
	void updateXScale(float x);
	void updateYScale(float y);
	void updateScale(Vector3 scale);
	void setRadius(float r);
	void updateRadius(float r);
	void setVelocity(Vector2 v);
	void setMaxSpeed(float v);
	void setCurrentSpeed(float v);

	//Get private members
	float getX() const;
	float getY() const;
	Vector3 getPosition() const;
	float getRotation() const;
	float getAggroRange() const;
	int getEntitiesInRange() const;
	float getXScale() const;
	float getYScale() const;
	Vector3 getScale() const;
	float getRadius() const;
	Vector2 getVelocity() const;
	float getMaxSpeed() const;
	float getCurrentSpeed() const;

private:
	Vector3 position;
	float rotation;
	float aggroRange;
	int entitiesInRange;
	Vector3 scale;
	float radius;
	Vector2 velocity;
	float maxSpeed;
	float currentSpeed;

	Vector3 gridToFloat(int x, int y);
};