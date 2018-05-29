#pragma once
#include "../../nclgl/Vector3.h"
#include "Entity.h"
class Wall
{
public:
	Wall(Vector3 s, Vector3 e);
	~Wall();

	Vector3 getStart() const;
	Vector3 getEnd() const;
	float getLengthSquared() const;
	float getDot(Entity *e) const;
	bool pointOnLine(float closestX, float closestY) const;
	void setStart(Vector3 s);
	void setEnd(Vector3 e);
	

private:
	Vector3 start;
	Vector3 end;
	float lenSquared;
};

