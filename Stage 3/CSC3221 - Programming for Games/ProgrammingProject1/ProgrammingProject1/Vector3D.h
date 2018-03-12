#pragma once
#include <string>

class Vector3D {
protected:
	float x, y, z;
public:
	Vector3D();
	Vector3D(Vector3D &rhs);
	Vector3D(const Vector3D &rhs);
	Vector3D(float x, float y, float z);
	~Vector3D();
	float getX();
	float getY();
	float getZ();
	void setVector(float newX, float newY, float newZ);
	float getMagnitude();
	Vector3D operator+(Vector3D rhs);
	Vector3D operator-(Vector3D rhs);
	Vector3D scalarMultiply(float scalar);
	Vector3D scalarDivide(float scalar);
	float operator*(Vector3D rhs);
	Vector3D operator%(Vector3D rhs);
	Vector3D operator=(Vector3D rhs);
	bool operator==(Vector3D rhs);
	bool operator!=(Vector3D rhs);
	Vector3D unitVector();
	Vector3D orthogonalUnitVector(Vector3D rhs);
	std::string printVector();
};