#pragma once
#include <iostream>

using namespace std;

class Shape {

public:
	Shape();
	Shape(float x, float y);
	virtual ~Shape() = 0;
	float getXPos() const;
	float getYPos() const;
	void shiftX(float dx);
	void shiftY(float dy);
	void setX(float newX);
	void setY(float newY);

protected:
	float xPos;
	float yPos;

};