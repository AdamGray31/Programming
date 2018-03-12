#include "Square.h"
#include "Circle.h"
#include <cmath>
#include <algorithm>

using namespace std;

Square::Square() : Shape(1, 1), width(1) {}

Square::Square(float x, float y, float w) : Shape(x, y), width(w) {}

Square::~Square() {}

float Square::getWidth() const {
	return width;
}

//If the sum of the squares' widths is greater than the perpendicular distance between their centres they are colliding
bool Square::collision(Square square) {
	return (
		abs(this->getXPos() - square.getXPos()) < (this->getWidth() + square.getWidth()) &&
		abs(this->getYPos() - square.getYPos()) < (this->getWidth() + square.getWidth()) 
		);
}

bool Square::collision(Circle circle) {
	//Determine the closest point to the circle on the square
	float closestX = max(this->getXPos() - this->getWidth(), min(this->getXPos() + this->getWidth(), circle.getXPos()));
	float closestY = max(this->getYPos() - this->getWidth(), min(this->getYPos() + this->getWidth(), circle.getYPos()));

	//determine the distance to that point
	float distanceX = circle.getXPos() - closestX;
	float distanceY = circle.getYPos() - closestY;
	float distanceSquared = pow(distanceX, 2) + pow(distanceY, 2);

	//If the distance to this point is less than the radius, the shapes are colliding
	return distanceSquared < pow(circle.getRadius(), 2);
}

ostream& operator<<(ostream& os, const Square& square) {
	os << "Square(x=" << square.getXPos() << ", y=" << square.getYPos() << ", width=" << square.getWidth() << ")";
	return os;
}