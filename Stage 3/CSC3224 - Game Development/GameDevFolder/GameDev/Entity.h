#pragma once
#include "../../nclgl/Vector2.h"

//Basic entity class to hold physical data about an entity

class Entity
{
public:
	Entity();
	~Entity();

	Vector2 getPosition();
	Vector2 getVelocity();
	float getRotation();
	float getDepth();
	float getRadius();

	void setPosition(Vector2 position);
	void updatePosition();
	void setVelocity(Vector2 velocity);
	void updateVelocity(Vector2 velocity);
	void setRotation(float rotation);
	void updateRotation(float rotation);
	void setDepth(float depth);
	void updateDepth(float depth);
	void setRadius(float radius);

private:
	Vector2 position;
	Vector2 velocity;
	float depth;
	float rotation;
	float radius;
};

