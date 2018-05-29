#pragma once

#include <vector>
#include <time.h>
#include "../../nclgl/window.h"
#include "../../nclgl/Vector3.h"
#include "Entity.h"
#include "Leader.h"
#include "Dragon.h"
#include "Follower.h"
#include "Wall.h"
#include "Node.h"

using std::vector;

//Approx 5 feet
static const float GRIDSQUARE = 26.66f;

//Approx 5 feet per second 
static const float RAIDERVELOCITY = 0.0266f;

//Approx 3 feet per second
static const float DRAGONVELOCITY = RAIDERVELOCITY * 0.6f;

//Approx 15 feet per second
static const float ARROWVELOCITY = RAIDERVELOCITY * 3.0f;

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
	vector<Entity*> arrows;
	Leader* leader;
	vector<Entity*> entities;
	vector<Entity*> rocks;
	vector<Entity*> rubble; 
	Entity* pool;
	vector<Wall*> walls;
	
	
private:
	
	int		numEntities;
	int		numRaiders;
	int		breathState;
	bool	dragonState;
	bool	gameStart;
	bool	aiDemo;
	float	arrowAliveTime;
	float	arrowCooldown;
	float	cooldownPeriod;
	bool	hoardPathing;
	bool	poolPathing;

	Node nodes[49][35] = {};

	Node* poolNode;
	Node* hoardNode;

	float timeSinceLastUpdate;

	void planPath();
	void moveLeader(float msec);
	void updateRaiders(float msec);
	void updateDragon(float msec);
	void collisionDetection(float msec);
	void collisionResponse(Entity* e1, Entity* e2);
	void updatePositions(float msec);
	void debugKeys();
	void displayInfo(float msec);
	void startGame();

};