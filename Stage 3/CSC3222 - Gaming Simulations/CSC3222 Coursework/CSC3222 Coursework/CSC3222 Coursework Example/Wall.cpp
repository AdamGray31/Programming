#include "Wall.h"



Wall::Wall(Vector3 s, Vector3 e)
{
	start = s;
	end = e;
	lenSquared = pow(s.x - e.x, 2) + pow(s.y - e.y, 2);
}

Wall::~Wall()
{
}

Vector3 Wall::getStart() const
{
	return start;
}

Vector3 Wall::getEnd() const
{
	return end;
}

float Wall::getLengthSquared() const
{
	return lenSquared;
}

//Returns dot product of wall with entity pos
float Wall::getDot(Entity *e) const
{
	return
		(((e->getPhysicsNode()->getX() - start.x) * (end.x - start.x)) +
		((e->getPhysicsNode()->getY() - start.y) * (end.y - start.y))) / 
		lenSquared;
}

bool Wall::pointOnLine(float closestX, float closestY) const
{

	float d1Sq =
		pow(closestX - start.x, 2) +
		pow(closestY - start.y, 2);

	float d2Sq =
		pow(closestX - end.x, 2) +
		pow(closestY - end.y, 2);

	return d1Sq + d2Sq <= lenSquared;
}
  
void Wall::setStart(Vector3 s)
{
	start = s;
}

void Wall::setEnd(Vector3 e)
{
	end = e;
}
