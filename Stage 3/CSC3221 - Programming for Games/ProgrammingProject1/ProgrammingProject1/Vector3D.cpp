#pragma once
#include "Vector3D.h"
#include <math.h>
#include <iostream>

//Default constructor sets all components to zero
Vector3D::Vector3D() : x(0), y(0), z(0) {

}

//Set components to supplied values
Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {

}

//Copy constructors
Vector3D::Vector3D(Vector3D &rhs) {
	x = rhs.getX();
	y = rhs.getY();
	z = rhs.getZ();
}
Vector3D::Vector3D(const Vector3D &rhs) {
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

//Destructor
Vector3D::~Vector3D() {

}

//Return x component
float Vector3D::getX() {
	return x;

}

//Return y component
float Vector3D::getY() {
	return y;
}

//Return z component
float Vector3D::getZ() {
	return z;
}

//Set components to new supplied values
void Vector3D::setVector(float newX, float newY, float newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

//Return magnitude of a 3d vector
float Vector3D::getMagnitude() {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//Add components of two vectors
Vector3D Vector3D::operator+(Vector3D rhs) {
	return Vector3D(
		x + rhs.getX(), 
		y + rhs.getY(), 
		z + rhs.getZ());
}

//Subtract components of two vectors
Vector3D Vector3D::operator-(Vector3D rhs) {
	return Vector3D(
		x - rhs.getX(), 
		y - rhs.getY(), 
		z - rhs.getZ());
}

//Multiply by a Scalar
Vector3D Vector3D::scalarMultiply(float scalar) {
	return Vector3D(
		x*scalar,
		y*scalar,
		z*scalar
	);
}

//Divide by a Scalar
Vector3D Vector3D::scalarDivide(float scalar) {
	return Vector3D(
		x / scalar,
		y / scalar,
		z / scalar
	);
}

//Dot product
float Vector3D::operator*(Vector3D rhs) {
	return x*rhs.getX() + y*rhs.getY() + z*rhs.getZ();
}

//Vector product
Vector3D Vector3D::operator%(Vector3D rhs) {
	return Vector3D(
		y*rhs.getZ() - z*rhs.getY(),
		z*rhs.getX() - x*rhs.getZ(),
		x*rhs.getY() - y*rhs.getX());
}

//Assignment operator
Vector3D Vector3D::operator=(Vector3D rhs) {
	if (*this != rhs) {
		x = rhs.getX();
		y = rhs.getY();
		z = rhs.getZ();
	}
	return *this;
}

//Equal operator
bool Vector3D::operator==(Vector3D rhs) {
	return (x == rhs.getX() && y == rhs.getY() && z == rhs.getZ());
}

bool Vector3D::operator!=(Vector3D rhs) {
	return !(operator==(rhs));
}

//Returns a unit vector in the same direction as the current vector
Vector3D Vector3D::unitVector() {
	if (getMagnitude() == 0.0f) {
		std::cout << "Cannot get unitVector of a vector with zero magnitude (Returning (0,0,0)).\n";
		return Vector3D();
	}
	return scalarDivide(getMagnitude());
}

//Return an orthogonal unit vector
Vector3D Vector3D::orthogonalUnitVector(Vector3D rhs) {
	return (*this % rhs).unitVector();
}

std::string Vector3D::printVector() {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}
