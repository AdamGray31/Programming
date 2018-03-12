#include "Shape.h"
#include "Circle.h"
#include "Square.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

//Constants
static const int GRID_SIZE = 200;
static const int NUMBER_OF_SHAPES = 30;
static const int MAX_SHAPE_SIZE = 3;


int main(void) {

	//Display constants
	cout << "Grid Size: " << GRID_SIZE << "\nNumber of Shapes: " << NUMBER_OF_SHAPES << "\nMax Shape Size: " << MAX_SHAPE_SIZE << "\n";

	//Set random seed 
	srand(time(NULL));

	//The Vector that will store shapes
	vector<Shape*> shapes;

	for (int i = 0; i < NUMBER_OF_SHAPES; ++i) {
		//Flip a coin, if heads, create a square, if tails, create a circle
		if (rand() % 2 == 0) {
			//Create a square somewhere in the grid, with width between 0.01 and MAX_SHAPE_SIZE
			shapes.push_back(new Square(rand() % GRID_SIZE, rand() % GRID_SIZE, (rand() % 100*MAX_SHAPE_SIZE + 1)/100.0f));
		}
		else {
			//Create a circle somewhere in the grid, with a radius between 0.01 and MAX_SHAPE_SIZE
			shapes.push_back(new Circle(rand() % GRID_SIZE, rand() % GRID_SIZE, (rand() % 100*MAX_SHAPE_SIZE + 1)/100.0f));
		}
		
	}

	vector<Shape*> toRemove;

	//While the vector has more than one shape, remove colliding shapes until at most one remains
	do {
		

		//Move all the shapes by a small amount
		for (vector<Shape*>::iterator moveIterator = shapes.begin(); moveIterator != shapes.end(); ++moveIterator) {

			Shape* shape = *moveIterator;
			//Move the shape by (-10 to 10) in X and Y 
			shape->shiftX((rand() % 200 - 100) / 10.0f);
			shape->shiftY((rand() % 200 - 100) / 10.0f);
			
			//If the shape has moved outside the grid, move it back in
			if (shape->getXPos() > GRID_SIZE) {
				shape->setX(GRID_SIZE - 0.01f);
			}
			if (shape->getXPos() < 0.0f) {
				shape->setX(0.1f);
			}
			if (shape->getYPos() > GRID_SIZE) {
				shape->setY(GRID_SIZE - 0.01f);
			}
			if (shape->getYPos() < 0.0f) {
				shape->setY(0.1f);
			}
		}

		//Loop through shapes again, looking for collisions
		//If a collision is detected, add both shapes to 'toRemove' and output them to the console
		for (vector<Shape*>::iterator it1 = shapes.begin(); it1 != shapes.end(); ++it1) {

			//If the shape has already collided, skip it
			if (find(toRemove.begin(), toRemove.end(), *it1) != toRemove.end()) {
				continue;
			}

			Shape* abstractShape1 = *it1;

			//If shape1 is a Square:
			if (Square* shape1 = dynamic_cast<Square*>(abstractShape1)) {
				//Loop through remaining shapes in 'shapes' vector
				for (vector<Shape*>::iterator it2 = it1 + 1; it2 != shapes.end(); ++it2) {

					//If the shape has already collided, skip it
					if (find(toRemove.begin(), toRemove.end(), *it2) != toRemove.end()) {
						continue;
					}

					Shape* abstractShape2 = *it2;
					//If second shape is a square, test Square.collision(Square)
					if (Square* shape2 = dynamic_cast<Square*>(abstractShape2)) {
						if (shape1->collision(*shape2)) {
							toRemove.push_back(*it1);
							toRemove.push_back(*it2);
							cout << *shape1 << " collided with " << *shape2 << "\n";
							break;
						}
					}
					//If second shape is a circle, test Square.collision(Circle)
					else if (Circle* shape2 = dynamic_cast<Circle*>(abstractShape2)) {
						if (shape1->collision(*shape2)) {
							toRemove.push_back(*it1);
							toRemove.push_back(*it2);
							cout << *shape1 << " collided with " << *shape2 << "\n";
							break;
						}
					}
				}
			}
			//If shape1 is a Circle:
			else if (Circle* shape1 = dynamic_cast<Circle*>(abstractShape1)) {
				for (vector<Shape*>::iterator it2 = it1 + 1; it2 != shapes.end(); ++it2) {

					//If the shape has already collided, skip it
					if (find(toRemove.begin(), toRemove.end(), *it2) != toRemove.end()) {
						continue;
					}

					Shape* abstractShape2 = *it2;
					//If second shape is a square, test Circle.collision(Square)
					if (Square* shape2 = dynamic_cast<Square*>(abstractShape2)) {
						if (shape1->collision(*shape2)) {
							toRemove.push_back(*it1);
							toRemove.push_back(*it2);
							cout << *shape1 << " collided with " << *shape2 << "\n";
							break;
						}
					}
					//If second shape is a circle, test Circle.collision(Circle)
					else if (Circle* shape2 = dynamic_cast<Circle*>(abstractShape2)) {
						if (shape1->collision(*shape2)) {
							toRemove.push_back(*it1);
							toRemove.push_back(*it2);
							cout << *shape1 << " collided with " << *shape2 << "\n";
							break;
						}
					}
				}
			}
		}

		//Loop through each shape that has collided and remove it from the 'shapes' vector
		for (vector<Shape*>::iterator it = toRemove.begin(); it != toRemove.end(); ++it) {
			shapes.erase(remove(shapes.begin(), shapes.end(), *it), shapes.end());
		}
	
	} while (shapes.size() > 1);

	//Delete the objects in the toRemove vector
	for (int i = 0; i < toRemove.size(); ++i) {
		delete toRemove[i];
	}
	toRemove.clear();

	//Print out the last shape if one remains, otherwise state so
	if (shapes.size() < 1) {
		cout << "No more shapes remain!\n";
	}
	else if (Square* shape = dynamic_cast<Square*>(shapes[0])) {
		cout << "Final shape is " << *shape << "\n";
		delete shape, shapes[0];
	}
	else if (Circle* shape = dynamic_cast<Circle*>(shapes[0])) {
		cout << "Final shape is " << *shape << "\n";
		delete shape, shapes[0];
	}
	shapes.clear();
	
	//Exit
	int exit;
	cin >> exit;
	return 0;
}
