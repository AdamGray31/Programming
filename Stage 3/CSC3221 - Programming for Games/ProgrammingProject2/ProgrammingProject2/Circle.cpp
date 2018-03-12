#include "Circle.h"
#include "Square.h"
#include <cmath>
#include <algorithm>

using namespace std;

Circle::Circle() : Shape(1, 1), radius(1) {}

Circle::Circle(float x, float y, float r): Shape(x,y), radius(abs(r)) {}

Circle::~Circle() {}

float Circle::getRadius() const {
	return radius;
}

//If the two radii are greater than the distance between the circles' centres then they are colliding
bool Circle::collision(Circle circle) {
	return (
		pow(this->getRadius() + circle.getRadius(), 2.0f) > 
		pow((this->getXPos()) - circle.getXPos(), 2.0f) + 
		pow((this->getYPos() - circle.getYPos()), 2.0f)
		);
}

bool Circle::collision(Square square) {
	
	//Determine the closest point to the circle on the square
	float closestX = max(square.getXPos() - square.getWidth(), min(square.getXPos() + square.getWidth(), this->getXPos()));
	float closestY = max(square.getYPos() - square.getWidth(), min(square.getYPos() + square.getWidth(), this->getYPos()));

	//determine the distance to that point
	float distanceX = this->getXPos() - closestX;
	float distanceY = this->getYPos() - closestY;
	float distanceSquared = pow(distanceX, 2) + pow(distanceY, 2);
	
	//If the distance to this point is less than the radius, the shapes are colliding
	return distanceSquared < pow(this->getRadius(), 2);

}

ostream& operator<<(ostream& os, const Circle& circle) {
	os << "Circle(x=" << circle.getXPos() << ", y=" << circle.getYPos() << ", radius=" << circle.getRadius() << ")";
	return os;
}