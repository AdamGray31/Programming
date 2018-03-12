#pragma once
#include "Vector3D.h"
#include "Bin.h"
#include <iostream>

using namespace std;

int main() {

	Vector3D defaultVec = Vector3D();
	cout << "Default constructor gives: " << defaultVec.printVector() << "\n";
	cout << "\n";

	Vector3D a = Vector3D(1, 6, 9);

	cout << "Constructor with parameters (1,6,9) gives: " << a.printVector() << "\n";
	cout << "\n";

	Vector3D b = Vector3D(2, 3, 4);
	
	Vector3D aUnit = a.unitVector();

	cout << "X of a = " << a.getX() << ", Y of a = " << a.getY() << ", Z of a = " << a.getZ() << "\n";
	cout << "a = " << a.printVector() << "\n";
	cout << "b = " << b.printVector() << "\n";
	cout << "\n";
	cout << "a + b = " << (a + b).printVector() << "\n";
	cout << "a - b = " << (a - b).printVector() << "\n";
	cout << "a * 5 = " << (a.scalarMultiply(5)).printVector() << "\n";
	cout << "a / 5 = " << (a.scalarDivide(5)).printVector() << "\n";
	cout << "a . b = " << (a * b) << "\n";
	cout << "a x b = " << (a % b).printVector() << "\n";
	cout << "\n";

	cout << "Unit vector of a = " << aUnit.printVector() << "\n";
	cout << "magnitude of a = " << a.getMagnitude() << "\n";
	cout << "magnitude of aUnit = " << aUnit.getMagnitude() << "\n";
	cout << "\n";

	Vector3D orth1 = Vector3D(1, 1, 1);
	Vector3D orth2 = Vector3D(-1, -1, -1);
	cout << "orth1 = " << orth1.printVector() << "\n";
	cout << "orth2 = " << orth2.printVector() << "\n";
	cout << "Trying orth1.orthogonalVector(orth2);\n";
	cout << (orth1.orthogonalUnitVector(orth2)).printVector() << "\n";
	cout << "\n";

	Vector3D copy1 = Vector3D(1, 2, 3);
	Vector3D copy2 = Vector3D(4, 5, 6);
	

	cout << "Before copy1=copy2;\n";
	cout << "copy1: " << copy1.printVector() << "\n";
	cout << "copy2: " << copy2.printVector() << "\n";

	copy1 = copy2;

	cout << "After\n";
	cout << "copy1: " << copy1.printVector() << "\n";
	cout << "copy2: " << copy2.printVector() << "\n";
	cout << "\n";

	Vector3D copy3 = Vector3D(copy2);
	cout << "Vector3D copy3 = Vector3D(copy2);\n";
	cout << "copy3: " << copy3.printVector() << "\n";
	cout << "\n";

	cout << "\n";
	
	Bin bin = Bin();
	bin.add(1, 1, 1);
	bin.add(2, 2, 2);
	bin.add(3, 3, 3);
	bin.add(4, 4, 4);
	Bin bin2 = Bin(bin);
	bin.printVectors();
	bin2.printVectors();
	bin.remove(2);
	bin.printVectors();
	bin2.printVectors();

	Bin bin3 = Bin(5);
	bin3.add(1, 1, 1);
	bin3.add(2, 2, 2);
	cout << "bin3 Size is " << bin3.getBinSize()<< "\n";
	bin3.printVectors();
	int exit;
	cin >> exit;

	return 0;
}