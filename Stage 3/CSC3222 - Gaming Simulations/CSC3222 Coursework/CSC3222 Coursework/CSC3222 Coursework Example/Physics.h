#pragma once

#include <vector>
#include "../../nclgl/window.h"
#include "../../nclgl/Vector3.h"
#include "Entity.h"
#include "Leader.h"
#include "Dragon.h"
#include "Follower.h"

using std::vector;

//Approx 5 feet
static const float GRIDSQUARE = 26.66f;

//Approx 5 feet per second 
static const float RAIDERVELOCITY = 0.0266f;

//Approx 3 feet per second
static const float DRAGONVELOCITY = RAIDERVELOCITY * 0.6f;

//Defines speed of leader's rotation
static const float LEADERROT = 0.2f;

//Defines radius of a raider
static const float RAIDERRADIUS = GRIDSQUARE * 0.4f;

//Defines radius of dragon
static const float DRAGONRADIUS = GRIDSQUARE * 1.5f;


class Physics {

public:
	Physics();
	~Physics();

	void UpdatePhysics(float msec);

	Entity* map;
	Dragon* dragon;
	Entity* breath;
	vector<Follower*> raiders;
	Leader* leader;
	vector<Entity*> entities;
	vector<Entity*> rocks;

private:
	
	int		numEntities;
	int		numRaiders;
	int		numRocks;
	int		breathState;
	bool	dragonState;
	bool	gameStart;
	bool	aiDemo;

	void moveLeader(float msec);
	void updateRaiders(float msec);
	void updateDragon(float msec);
	void collisionDetection(float msec);
	void collisionResponse(float msec, Entity* e1, Entity* e2);
	void startGame();

};