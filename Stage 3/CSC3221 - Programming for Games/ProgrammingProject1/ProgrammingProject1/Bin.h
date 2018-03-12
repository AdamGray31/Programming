#pragma once
#include "Vector3D.h"

class Bin {
protected:
	Vector3D* vectors;
	int binSize;
	void copy(const Bin& rhs);
public:
	Bin();
	Bin(int binSize);
	Bin(const Bin &rhs);
	~Bin();
	int getBinSize();
	float getX(int a);
	float getY(int a);
	float getZ(int a);
	void add(float x, float y, float z);
	void remove(int b);
	Bin & operator=(const Bin & rhs);
	void printVectors();
};