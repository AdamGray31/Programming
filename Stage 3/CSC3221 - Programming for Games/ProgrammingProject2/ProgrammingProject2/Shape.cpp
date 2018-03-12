#include "Shape.h"

Shape::Shape() {}

Shape::Shape(float x, float y) : xPos(x), yPos(y) {}

Shape::~Shape() {}

float Shape::getXPos() const { return xPos;}

float Shape::getYPos() const { return yPos;}

void Shape::shiftX(float dx) { xPos += dx;}

void Shape::shiftY(float dy) { yPos += dy;}

void Shape::setX(float newX) { xPos = newX; }

void Shape::setY(float newY) { yPos = newY; }
