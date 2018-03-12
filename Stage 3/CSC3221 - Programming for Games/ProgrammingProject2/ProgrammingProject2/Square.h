#pragma once
#include "Shape.h"
#ifndef CIRCLE_H
#define CIRCLE_H
#endif
using namespace std;

class Circle;

class Square : public Shape {

public:
	Square();
	Square(float x, float y, float width);
	~Square();
	float getWidth() const;
	bool collision(Square square);
	bool collision(Circle circle);
	friend ostream& operator<<(ostream& os, const Square& square);

protected:
	//Square's width is perpendicular distance from its centre to any edge
	float width;

};

