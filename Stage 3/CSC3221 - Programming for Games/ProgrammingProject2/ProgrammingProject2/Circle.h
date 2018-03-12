#pragma once
#include "Shape.h"
#ifndef SQUARE_H
#define SQUARE_H
#endif
using namespace std;

class Square;

class Circle : public Shape {

public:
	Circle();
	Circle(float x, float y, float r);
	~Circle();
	float getRadius() const;
	bool collision(Circle circle);
	bool collision(Square square);
	friend ostream& operator<<(ostream& os, const Circle& circle);

protected:

	float radius;

};

