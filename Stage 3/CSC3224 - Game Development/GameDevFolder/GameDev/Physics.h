#pragma once
#include <vector>
#include <iostream>
#include "Event.h"
#include "Entity.h"
using namespace std;

//Basic physics class which determines state of entities

enum entityList
{
	map,
	player,
	playerShot,
	grenade,
	enemy
};

class Physics {

public:
	Physics();
	bool updatePhysics(float msec, vector<Event>* events, vector<Entity*>* entities);	
private:
	float time;
};



