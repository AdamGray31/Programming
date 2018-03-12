#pragma once
#include "Bin.h"
#include <iostream>

//Set infinity x,y,z vector to be NULLVEC
static const Vector3D NULLVEC = Vector3D(INFINITY, INFINITY, INFINITY);

//Default Constructor
Bin::Bin():binSize(0) {
	vectors = new Vector3D[binSize];
}

//Create new bin with all the vectors set to infinity
Bin::Bin(int binSize):binSize(binSize) {
	vectors = new Vector3D[binSize];
	for (int i = 0; i < binSize; i++) {
		vectors[i] = NULLVEC;
	}
}

//copy Constructor
Bin::Bin(const Bin& rhs) {
	this->copy(rhs);
}

void Bin::copy(const Bin& rhs) {
	binSize = rhs.binSize;
	vectors = new Vector3D[binSize];
	for (int i = 0; i < binSize; i++) {
		vectors[i] = rhs.vectors[i];
	}
}

//Destructor
Bin::~Bin() {
		delete[] vectors;
}

//Return the size of the Bin
int Bin::getBinSize() {
	return binSize;
}

//Return the x value of the a'th vector 
float Bin::getX(int a) {
	
	return (vectors + a)->getX();

}

//Return the y value of the a'th vector 
float Bin::getY(int a) {

	return (vectors + a)->getY();;

}
//Return the z value of the a'th vector 
float Bin::getZ(int a) {

	return (vectors + a)->getZ();

}

//Add a new Vector3D onto the end of the bin
void Bin::add(float x, float y, float z) {

	//Check if there is a space in the bin
	for (int i = 0; i < binSize; i++) {
		if (vectors[i] == NULLVEC) {
			vectors[i] = Vector3D(x, y, z);
			return;
		}
	}

	//Otherwise add onto the end opf the bin
	binSize++;
	Vector3D* copies = new Vector3D[binSize];
	for (int i = 0; i < binSize - 1; i++) {
		copies[i] = vectors[i];
	}
	copies[binSize - 1] = Vector3D(x, y, z);
	delete[] vectors;
	vectors = copies;

}

//Remove the b'th Vector3D and move remaining Vectors up
void Bin::remove(int b) {
	//Exit if b is outside of the range or the bin is empty, or trying to remove a 'null' vector
	if (binSize == 0 || b>binSize || b<0 || vectors[b] == NULLVEC) {
		return;
	}
	binSize--;
	Vector3D* copies = new Vector3D[binSize];
	for (int i = 0; i < b; i++) {
		copies[i] = vectors[i];
	}
	for (int i = b; i < binSize; i++) {
		copies[i] = vectors[i + 1];
	}
	delete[] vectors;
	vectors = copies;
	
}

//Assignment operator
Bin& Bin::operator=(const Bin& rhs) {
	if (this == &rhs) {
		return *this;
	}
	delete[] vectors;
	this->copy(rhs);
	return *this;
}

//Print out vectors array locally
void Bin::printVectors() {
	for (int i = 0; i < binSize; i++) {
		if (vectors[i] == NULLVEC) {
			break;
		}
		std::cout << "Vector[" << i << "] = " << vectors[i].printVector() << "\n";
	}
	std::cout << "\n";
}