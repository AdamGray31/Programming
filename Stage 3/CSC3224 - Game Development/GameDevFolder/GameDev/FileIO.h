#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Entity.h"

//Reads in files and sets up levels

using namespace std;

class FileIO
{
public:
	FileIO(vector<Entity*>* entities);
	~FileIO();
	void readLevelFile(char* levelFile);
	void nextLevel();

private:
	int currentLevel;

	Entity* map;
	Entity* player;
	Entity* playerShot;
	Entity* grenade;
	Entity* enemy;
	vector<Entity*> walls;

};