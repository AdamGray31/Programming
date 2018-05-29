#include "Physics.h"



Physics::Physics()
{

	srand(time(NULL));

	numRaiders = 15;
	numEntities = numRaiders + 2;
	arrowCooldown = 6000.0f;
	cooldownPeriod = 6000.0f;
	arrowAliveTime = 2000.0f;

	leader = new Leader(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, RAIDERRADIUS,  0.0f, Vector3(10.0f, 10.0f, 1.0f)));
	leader->getPhysicsNode()->setMaxSpeed(RAIDERVELOCITY);
	entities.push_back(leader);

	for (int i = 0; i < numRaiders; i++)
	{
		raiders.push_back(new Follower(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, RAIDERRADIUS, 0.0f, Vector3(10.0f, 10.0f, 1.0f))));
		raiders.at(i)->getPhysicsNode()->setMaxSpeed(RAIDERVELOCITY);
		entities.push_back(raiders.at(i));

		arrows.push_back(new Entity(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, RAIDERRADIUS, 0.0f, Vector3(20.0f, 20.0f, 1.0f))));
		arrows.at(i)->getPhysicsNode()->setMaxSpeed(ARROWVELOCITY);
	}
	//Init rocks
	{
		rocks.push_back(new Entity(new PhysicsNode(Vector3(47.41f, -201.39f, 0.0f), 0.0f, 0.75f * GRIDSQUARE)));
		rocks.push_back(new Entity(new PhysicsNode(Vector3(-167.68f, -281.90f, 0.0f), 0.0f, 0.75f * GRIDSQUARE)));
		rocks.push_back(new Entity(new PhysicsNode(Vector3(-275.33f, -328.21f, 0.0f), 0.0f, GRIDSQUARE)));
		rocks.push_back(new Entity(new PhysicsNode(Vector3(-586.27f, -81.71f, 0.0f), 0.0f, 2 * GRIDSQUARE)));
		rocks.push_back(new Entity(new PhysicsNode(Vector3(-542.51f, 198.62f, 0.0f), 0.0f, 2 * GRIDSQUARE)));
		rocks.push_back(new Entity(new PhysicsNode(Vector3(-80.48f, 267.26f, 0.0f), 0.0f, 2 * GRIDSQUARE)));
		rocks.push_back(new Entity(new PhysicsNode(Vector3(105.44f, 367.33f, 0.0f), 0.0f, 2 * GRIDSQUARE)));
		rocks.push_back(new Entity(new PhysicsNode(Vector3(499.93f, 364.74f, 0.0f), 0.0f, 1.5f * GRIDSQUARE)));
		rocks.push_back(new Entity(new PhysicsNode(Vector3(152.89f, 38.73f, 0.0f), 0.0f, GRIDSQUARE)));
	}
	//Init rubble
	{
		rubble.push_back(new Entity(new PhysicsNode(Vector3(-434.22, -170.51, 0), 0.0f, 2 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(-438.43, -74.11, 0), 0.0f, 3 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(-267.77, 30.60, 0), 0.0f, 3 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(-182.29, 149.77, 0), 0.0f, 2.5 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(-3.68, 105.21, 0), 0.0f, 1.5 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(32.69, 244.30, 0), 0.0f, 2 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(140.63, 193.78, 0), 0.0f, 3 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(247.38, 263.08, 0), 0.0f, 3 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(338.81, 342.94, 0), 0.0f, 3 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(257.82, 116.95, 0), 0.0f, 2 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(635.49, 258.79, 0), 0.0f, 5 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(612.51, 68.52, 0), 0.0f, 3 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(550.15, -44.66, 0), 0.0f, 2 * GRIDSQUARE)));
		rubble.push_back(new Entity(new PhysicsNode(Vector3(-280.86, 555.98, 0), 0.0f, 3 * GRIDSQUARE)));
	}
	//Init walls
	{
		walls.push_back(new Wall(Vector3(25.23, -415.82, 0), Vector3(-64.47, -349.99, 0)));	//0
		walls.push_back(new Wall(walls.at(0)->getEnd(), Vector3(-146.56, -419.44, 0)));		//1
		walls.push_back(new Wall(walls.at(1)->getEnd(), Vector3(-343.82, -413.40, 0)));		//2
		walls.push_back(new Wall(walls.at(2)->getEnd(), Vector3(-695.12, -30.86, 0)));		//3
		walls.push_back(new Wall(walls.at(3)->getEnd(), Vector3(-532.07, 366.44, 0)));		//4
		walls.push_back(new Wall(walls.at(4)->getEnd(), Vector3(-258.99, 387.71, 0)));		//5
		walls.push_back(new Wall(walls.at(5)->getEnd(), Vector3(-371.58, 453.73, 0)));		//6
		walls.push_back(new Wall(walls.at(6)->getEnd(), Vector3(-322.64, 574.29, 0)));		//7
		walls.push_back(new Wall(walls.at(7)->getEnd(), Vector3(-142.42, 601.95, 0)));		//8
		walls.push_back(new Wall(walls.at(8)->getEnd(), Vector3(50.85, 516.75, 0)));		//9
		walls.push_back(new Wall(walls.at(9)->getEnd(), Vector3(-231.48, 239.09, 0)));		//10
		walls.push_back(new Wall(walls.at(10)->getEnd(), Vector3(-325.36, 295.08, 0)));		//11
		walls.push_back(new Wall(walls.at(10)->getEnd(), Vector3(372.41, 487.70, 0)));		//12
		walls.push_back(new Wall(walls.at(12)->getEnd(), Vector3(652.66, 281.46, 0)));		//13
		walls.push_back(new Wall(walls.at(13)->getEnd(), Vector3(620.27, -34.62, 0)));		//14
		walls.push_back(new Wall(walls.at(14)->getEnd(), Vector3(138.95, -63.68, 0)));		//15
		walls.push_back(new Wall(walls.at(15)->getEnd(), Vector3(323.47, -387.09, 0)));		//16
	}
	
	pool = new Entity(new PhysicsNode(Vector3(448.08, 91.48, 0), 0.0f, 2 * GRIDSQUARE));

	map = new Entity(new PhysicsNode(Vector3(0.0f, 100.0f, -200.0f), 0.0f, 0.0f, 0.0f, Vector3(864.0f, 540.0f, 100.0f)));

	dragon = new Dragon(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, DRAGONRADIUS, 4*GRIDSQUARE, Vector3(50.0f, 50.0f, 1.0f)));
	entities.push_back(dragon);
	dragon->getPhysicsNode()->setMaxSpeed(DRAGONVELOCITY);
	dragonState = 1;

	breath = new Entity(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, GRIDSQUARE,0.0f, Vector3(2.0f, 1.0f, 1.0f)));
	breathState = 1;

	timeSinceLastUpdate = 0.0f;

	//Initialise node positions
	int i = 0;
	int j = 0;
	for (float x = -26 * GRIDSQUARE; x <= 22 * GRIDSQUARE; x += GRIDSQUARE)
	{
		for (float y = 21 * GRIDSQUARE; y >= -14 * GRIDSQUARE; y -= GRIDSQUARE)
		{
			nodes[i][j] = Node(x, y);
			j++;
		}
		j = 0;
		i++;
	}

	//Add neighbours to each node
	for (int x = 0; x < 49; x++)
	{
		for (int y = 0; y < 35; y++)
		{
			//Add lateral neighbours
			if (x > 0)
			{
				nodes[x][y].addConnectedNode(&nodes[x - 1][y]);
			}
			if (y > 0)
			{
				nodes[x][y].addConnectedNode(&nodes[x][y - 1]);
			}
			if (x < 48)
			{
				nodes[x][y].addConnectedNode(&nodes[x + 1][y]);
			}
			if (y < 34)
			{
				nodes[x][y].addConnectedNode(&nodes[x][y + 1]);
			}
			//Add diagonal neighbours
			if (x > 0 && y > 0)
			{
				nodes[x][y].addConnectedNode(&nodes[x - 1][y - 1]);
			}
			if (x > 0 && y < 34)
			{
				nodes[x][y].addConnectedNode(&nodes[x - 1][y + 1]);
			}
			if (x < 48 && y > 0)
			{
				nodes[x][y].addConnectedNode(&nodes[x + 1][y - 1]);
			}
			if (x < 48 && y < 34)
			{
				nodes[x][y].addConnectedNode(&nodes[x + 1][y + 1]);
			}
		}
	}


	poolNode = &nodes[43][17];

	hoardNode = &nodes[21][3];

	poolPathing = false;
	hoardPathing = false;

}

Physics::~Physics()
{
	raiders.clear();
	entities.clear();
	rocks.clear();
	rubble.clear();
	walls.clear();
}

void Physics::UpdatePhysics(float msec)
{

	//Game Start
	if (Window::GetKeyboard()->Keyboard::KeyTriggered(KEYBOARD_K) && !gameStart) 
	{

		startGame();

	}
	
	//Launch Physics System
	if (gameStart) 
	{

		if (leader->isAlive()) 
		{
			moveLeader(msec);
		}
		
		planPath();

		updateRaiders(msec);

		updateDragon(msec);

		collisionDetection(msec);

		updatePositions(msec);

		debugKeys();

		displayInfo(msec);
				
	}

	
	
}

void Physics::collisionDetection(float msec) 
{

	//Loop through entities and check their collisions
	for (int i = 0; i < numEntities; ++i) 
	{
		Entity* e1 = entities.at(i);
		
		//Check Entity-Entity collision
		for (int j = i + 1; j < numEntities; ++j) 
		{
			Entity* e2 = entities.at(j);
			float distSq = e1->getDistanceSquared(e2);
			float radSumSq = pow(e1->getPhysicsNode()->getRadius() + e2->getPhysicsNode()->getRadius(), 2);
			if (distSq < radSumSq) 
			{
				collisionResponse(e1, e2);
			}
		}
		
		//Check Entity-Rock collisions
		for each(Entity* r in rocks) 
		{
			float distSq = e1->getDistanceSquared(r);
			float radSumSq = pow(e1->getPhysicsNode()->getRadius() + r->getPhysicsNode()->getRadius(), 2);
			if (distSq < radSumSq) 
			{
				e1->moveAway(r, msec);
			}
		}

		//Check Entity-Wall collision
		for each(Wall* w in walls)
		{
			//Get distance to closest point on wall
			//Dot product of wall and entity
			float entityDotWall = w->getDot(e1);
			float closestX = w->getStart().x + (entityDotWall * (w->getEnd().x - w->getStart().x));
			float closestY = w->getStart().y + (entityDotWall * (w->getEnd().y - w->getStart().y));

			//Make sure wall ends
			if (!w->pointOnLine(closestX, closestY))
			{
				continue;
			}

			float distSq = 
				pow(e1->getPhysicsNode()->getX() - closestX ,2) + 
				pow(e1->getPhysicsNode()->getY() - closestY ,2);

			float radSumSq =
				pow(2 * RAIDERRADIUS + e1->getPhysicsNode()->getRadius(), 2);

			if (distSq < radSumSq)
			{
				Entity* wallEntity = new Entity(new PhysicsNode(Vector3(closestX, closestY, 0), 0.0f, 0.0f));
				e1->moveAway(wallEntity, msec);
				delete wallEntity;
			}

		}


		e1->getPhysicsNode()->setCurrentSpeed(e1->getPhysicsNode()->getMaxSpeed());
		//Check Entity-Rubble collision
		for each(Entity* r in rubble) 
		{
			float distSq = e1->getDistanceSquared(r);
			float radSumSq = pow(e1->getPhysicsNode()->getRadius() + r->getPhysicsNode()->getRadius(), 2);
			if (distSq < radSumSq && e1 != dragon) 
			{
				e1->getPhysicsNode()->setCurrentSpeed(0.2f * e1->getPhysicsNode()->getMaxSpeed());
			}			
		}
	}

	/*
	
	I realise that this would cause damage to any raider within a certain radius of the dragon, 
	regardless of the direction the breath is facing, but it works for the purpose of this coursework
	
	*/
	//Check collision with dragon's breath (and calculate damage taken)
	//Leader damage/healing:
	if (leader->isAlive()) 
	{
		//Calculate damage from breath
		float distSq = leader->getDistanceSquared(dragon);
		float radSumSq = pow(leader->getPhysicsNode()->getRadius() + breath->getPhysicsNode()->getRadius() + dragon->getPhysicsNode()->getRadius(), 2);
		if (distSq < radSumSq) 
		{
			float damage = 50 * (msec / 1000.0f);
			leader->updateHP(-damage);
		}

		//Calculate healing if within pool
		distSq = leader->getDistanceSquared(pool);
		radSumSq = pow(leader->getPhysicsNode()->getRadius() + pool->getPhysicsNode()->getRadius(), 2);
		if (distSq < radSumSq)
		{
			float healing = 50 * (msec / 1000.0f);
			leader->updateHP(healing);
		}

	}
	else 
	{
		leader->setHP(0);
		leader->getPhysicsNode()->setPosition(3,-50);
	}

	//Raiders damage/healing:
	for each(Entity* raider in raiders) 
	{
		if (raider->isAlive()) 
		{
			//Calculate damage from breath
			float distSq = raider->getDistanceSquared(dragon);
			float radSumSq = pow(raider->getPhysicsNode()->getRadius() + breath->getPhysicsNode()->getRadius() + dragon->getPhysicsNode()->getRadius(), 2);
			if (distSq < radSumSq) 
			{
				float damage = 50 * (msec / 1000.0f);
				raider->updateHP(-damage);
			}

			//Calculate healing if within pool
			distSq = raider->getDistanceSquared(pool);
			radSumSq = pow(raider->getPhysicsNode()->getRadius() + pool->getPhysicsNode()->getRadius(), 2);
			if (distSq < radSumSq)
			{
				float healing = 50 * (msec / 1000.0f);
				raider->updateHP(healing);
			}

		}
		else 
		{
			raider->setHP(0);
			raider->getPhysicsNode()->setPosition(3, -50);
		}
	}

	//Dragon damage:
	
	for(int i = 0; i < numRaiders; ++i)
	{
		Entity* arrow = arrows.at(i);
		float distSq = arrow->getDistanceSquared(dragon);
		float radSumSq = pow(arrow->getPhysicsNode()->getRadius() + dragon->getPhysicsNode()->getRadius(), 2);
		if (distSq < radSumSq && dragon->isAlive()) 
		{
			dragon->updateHP(-raiders.at(i)->getDamage());
			arrow->getPhysicsNode()->setPosition(-100, -100);
			arrow->getPhysicsNode()->setVelocity(Vector2());
		}

		//If arrow collides with wall, remove it
		for each(Wall* w in walls)
		{
			//Get distance to closest point on wall
			//Dot product of wall and arrow
			float arrowDotWall = w->getDot(arrow);
			float closestX = w->getStart().x + (arrowDotWall * (w->getEnd().x - w->getStart().x));
			float closestY = w->getStart().y + (arrowDotWall * (w->getEnd().y - w->getStart().y));

			//Make sure wall ends
			if (!w->pointOnLine(closestX, closestY))
			{
				continue;
			}

			float distSq =
				pow(arrow->getPhysicsNode()->getX() - closestX, 2) +
				pow(arrow->getPhysicsNode()->getY() - closestY, 2);

			float radSumSq =
				pow(2 * RAIDERRADIUS + arrow->getPhysicsNode()->getRadius(), 2);

			if (distSq < radSumSq)
			{
				arrow->getPhysicsNode()->setPosition(-100, -100);
				arrow->getPhysicsNode()->setVelocity(Vector2());
			}
		}

	}

	if (!dragon->isAlive())
	{
		dragon->getPhysicsNode()->setPosition(-100, -100);
		dragon->getPhysicsNode()->setVelocity(Vector2());
	}

}

void Physics::collisionResponse(Entity* e1, Entity* e2) 
{

	Vector2 e1Pos = Vector2(e1->getPhysicsNode()->getPosition().x, e1->getPhysicsNode()->getPosition().y);
	Vector2 e2Pos = Vector2(e2->getPhysicsNode()->getPosition().x, e2->getPhysicsNode()->getPosition().y);

	//p
	float penDepth = e1->getPhysicsNode()->getRadius() + e2->getPhysicsNode()->getRadius() - sqrt(e1->getDistanceSquared(e2));
	//N
	Vector2 normalVector = e1Pos - e2Pos;
	normalVector.Normalise();
	//P
	Vector2 contactPoint = e1Pos - normalVector * (e1->getPhysicsNode()->getRadius() - penDepth);

	//Vab
	Vector2 velocitySum = e1->getPhysicsNode()->getVelocity() - e2->getPhysicsNode()->getVelocity();
	
	//VN
	float normalVelocity = Vector2::Dot(velocitySum, normalVector);
	
	//epsilon
	float epsilon = 0.8f;

	//Ma
	float e1Mass = e1->getMass();
	//Mb
	float e2Mass = e2->getMass();

	//J
	float J = 
		(-(1 + epsilon) * normalVelocity) / 
		(Vector2::Dot(normalVector, normalVector) * (1.0f / e1Mass + 1.0f / e2Mass));

	//J/Ma*N
	Vector2 e1Add = normalVector * (J / e1Mass);
	//J/Mb*N
	Vector2 e2Subtract = normalVector * (J / e2Mass);

	Vector2 e1NewV = e1->getPhysicsNode()->getVelocity() + e1Add;
	Vector3 e1NewP = e1->getPhysicsNode()->getPosition() + Vector3(penDepth * normalVector.x, penDepth * normalVector.y, 0.0f);
	Vector2 e2NewV = e2->getPhysicsNode()->getVelocity() - e2Subtract;
	Vector3 e2NewP = e2->getPhysicsNode()->getPosition() - Vector3(penDepth * normalVector.x, penDepth * normalVector.y, 0.0f);

	if (e1 != leader) 
	{
		//Correct for intersection
		e1->getPhysicsNode()->setPosition(e1NewP);
		//Set new velocity
		e1->getPhysicsNode()->setVelocity(e1NewV);
	}
	if (e2 != leader) 
	{
		//Correct for intersection
		e2->getPhysicsNode()->setPosition(e2NewP);
		//Set new velocity
		e2->getPhysicsNode()->setVelocity(e2NewV);
	}
	
}

void Physics::updatePositions(float msec)
{
	//Update Entity positions based on their velocities
	for each (Entity* e in entities)
	{
		e->getPhysicsNode()->updatePosition(e->getPhysicsNode()->getVelocity(), msec);
	}
	for each (Entity* a in arrows)
	{
		a->getPhysicsNode()->updatePosition(a->getPhysicsNode()->getVelocity(), msec);
	}
}

void Physics::debugKeys()
{
	//Make all raiders and dragon leave
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_0))
	{
		dragon->getPhysicsNode()->setPosition(Vector3(10000, 10000, 0));
		dragon->getPhysicsNode()->setCurrentSpeed(0);
		for each (Follower* raider in raiders)
		{
			raider->getPhysicsNode()->setPosition(Vector3(100000, 10000, 0));
			raider->getPhysicsNode()->setCurrentSpeed(0);
		}
	}

	//Make Dragon stop moving
	if (Window::GetKeyboard()->Keyboard::KeyTriggered(KEYBOARD_1))
	{
		dragonState = !dragonState;
	}

	//Display leader's position
	if (Window::GetKeyboard()->Keyboard::KeyTriggered(KEYBOARD_2))
	{
		cout << leader->getPhysicsNode()->getPosition() << "\n";
	}

}

void Physics::displayInfo(float msec)
{
	if (timeSinceLastUpdate >= 500.0f)
	{
		if (!leader->isAlive())
		{
			system("cls");
			cout
				<< "YOU LOSE!";
		}
		else if (!dragon->isAlive())
		{
			system("cls");
			cout
				<< "YOU WIN!";
		}
		else
		{
			system("cls");
			cout
				<< "Controls:\n"
				<< "K	: Start game\n"
				<< "J	: Select random raider to path to Hoard\n"
				<< "L	: Select weakest raider to path to Pool\n"
				<< "UP	: Move Forwards\n"
				<< "DOWN	: Move Backwards\n"
				<< "LEFT	: Turn Left\n"
				<< "RIGHT	: Turn Right\n"
				<< "SPACE	: Fire Arrows\n"
				<< "\n\n"
				<< "Arrow cooldown: " << 6 - arrowCooldown / 1000.0f << " seconds\n"
				<< "Leader HP:	" << leader->getHP() << "\n"
				<< "Dragon HP:	" << dragon->getHP() << "\n";

			for (int i = 0; i < numRaiders; ++i)
			{
				cout
					<< "Raider[" << i << "] HP:	" << raiders.at(i)->getHP() << "\n";
			}
		}
		timeSinceLastUpdate = 0.0f;
	}
	timeSinceLastUpdate += msec;
}

void Physics::planPath()
{
	//Pick random follower, send it to HOARD
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_J) && !hoardPathing)
	{
		Follower* pickedRaider = nullptr;
		int raiderNumber = rand() % numRaiders;
		int originalNumber = raiderNumber;
		pickedRaider = raiders.at(raiderNumber);
		while (!pickedRaider->isAlive())
		{
			raiderNumber = (raiderNumber + 1) % numRaiders;
			pickedRaider = raiders.at(raiderNumber);
			if (raiderNumber == originalNumber)
			{
				break;
			}
		}

		if (pickedRaider != nullptr)
		{
			int x = ((pickedRaider->getPhysicsNode()->getX() - 12.0f) / 26.66f) + 27;
			int y = ((pickedRaider->getPhysicsNode()->getY() + 2.0f) / 26.66f) + 21;
		
			Node* currentNode = &nodes[x][y];
			pickedRaider->pathTo(currentNode, hoardNode);
			pickedRaider->setTask(true, 0);
		}
		hoardPathing = true;
	}

	//Pick follower with lowest health, send it to POOL
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_L) && !poolPathing)
	{
		Follower* pickedRaider = nullptr;
		int lowestHP = 150;
		for each (Follower* raider in raiders) {
			if (raider->getHP() < lowestHP && raider->getHP() > 0)
			{
				pickedRaider = raider;
				lowestHP = pickedRaider->getHP();
			}
		}

		if (pickedRaider != nullptr)
		{
			int x = ((pickedRaider->getPhysicsNode()->getX() - 12.0f) / 26.66f) + 27;
			int y = ((pickedRaider->getPhysicsNode()->getY() + 2.0f) / 26.66f) + 21;

			Node* currentNode = &nodes[x][y];
			pickedRaider->pathTo(currentNode, poolNode);
			pickedRaider->setTask(true, 1);
		}
		poolPathing = true;
	}
}

void Physics::moveLeader(float msec)
{
	//Leader Rotation
	float shift = LEADERROT * msec;
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT)) 
	{
		leader->getPhysicsNode()->updateRotation(shift);
	}
	
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT)) 
	{
		leader->getPhysicsNode()->updateRotation(-shift);
	}

	//Leader Translation
	leader->getPhysicsNode()->setVelocity(Vector2(0, 0));
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_UP)) 
	{
		float rot = leader->getPhysicsNode()->getRotation();
		rot *= PI / 180;
		Vector2 temp = Vector2(cos(rot), sin(rot));

		leader->getPhysicsNode()->setVelocity(temp * leader->getPhysicsNode()->getMaxSpeed());
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN)) 
	{
		float rot = leader->getPhysicsNode()->getRotation();
		rot *= PI / 180;
		Vector2 temp = Vector2(cos(rot), sin(rot));

		leader->getPhysicsNode()->setVelocity(temp * leader->getPhysicsNode()->getMaxSpeed() * -1.0f);
	}
}

void Physics::updateRaiders(float msec) 
{

	//Launch raiders' arrows 
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE) && arrowCooldown == cooldownPeriod && leader->isAlive()) 
	{
		for (int i = 0; i < numRaiders; ++i) 
		{
			if (raiders.at(i)->isAlive()) 
			{
				arrows.at(i)->getPhysicsNode()->setCurrentSpeed(ARROWVELOCITY);
				arrows.at(i)->getPhysicsNode()->setPosition(raiders.at(i)->getPhysicsNode()->getPosition());
				arrows.at(i)->getPhysicsNode()->setRotation(raiders.at(i)->getPhysicsNode()->getRotation());
				float rot = arrows.at(i)->getPhysicsNode()->getRotation();
				rot *= PI / 180;
				Vector2 temp = Vector2(cos(rot), sin(rot));
				temp.Normalise();
				arrows.at(i)->getPhysicsNode()->setVelocity(temp * arrows.at(i)->getPhysicsNode()->getCurrentSpeed());
			}
		}
		arrowCooldown = 0.0f;
	}
	else if (arrowCooldown < cooldownPeriod) 
	{
		arrowCooldown += msec;
	}
	else 
	{
		arrowCooldown = cooldownPeriod;
	}

	if (arrowCooldown >= arrowAliveTime) 
	{
		for each (Entity* arrow in arrows) 
		{
			arrow->getPhysicsNode()->setPosition(-100, -100);
			arrow->getPhysicsNode()->setVelocity(Vector2());
		}
	}

	//Raider manipulation
	int raidersInRange = 0;

	for (int i = 0; i < numRaiders; i++) 
	{
		if (raiders.at(i)->isAlive()) 
		{
			
			//Rotate raiders
			raiders.at(i)->lookAt(dragon);

			//Count raiders within range of the dragon, set nearest as target
			if (raiders.at(i)->getDistanceSquared(dragon) <= pow(dragon->getPhysicsNode()->getAggroRange(), 2))
			{
				if (dragon->getTarget() == leader)
				{
					dragon->setTarget(raiders.at(i));
				}
				++raidersInRange;
			}
			
			if (!raiders.at(i)->isDoingTask())
			{
				//Make raiders follow Leader
				float rot = raiders.at(i)->getAngle(leader);
				rot *= PI / 180;
				Vector2 temp = Vector2(cos(rot), sin(rot));

				float max = raiders.at(i)->getPhysicsNode()->getMaxSpeed();

				raiders.at(i)->getPhysicsNode()->setVelocity(temp * max);
			}
			else if (raiders.at(i)->getTask() == 0)
			{
				int x = ((raiders.at(i)->getPhysicsNode()->getX() - 12.0f) / 26.66f) + 27;
				int y = ((raiders.at(i)->getPhysicsNode()->getY() + 2.0f) / 26.66f) + 21;

				Node* currentNode = &nodes[x][y];
				raiders.at(i)->pathTo(currentNode, hoardNode);
			}
			else if (raiders.at(i)->getTask() == 1)
			{
				int x = ((raiders.at(i)->getPhysicsNode()->getX() - 12.0f) / 26.66f) + 27;
				int y = ((raiders.at(i)->getPhysicsNode()->getY() + 2.0f) / 26.66f) + 21;

				Node* currentNode = &nodes[x][y];
				raiders.at(i)->pathTo(currentNode, poolNode);
			}
		}
	}
	dragon->getPhysicsNode()->setEntitiesInRange(raidersInRange);

}

void Physics::updateDragon(float msec) 
{	

	//If no raiders are within range, target the leader
	if (!dragon->getPhysicsNode()->getEntitiesInRange() && leader->isAlive()) 
	{
		dragon->setTarget(leader);
	}
	else 
	{
		float closestDistance = INFINITY;
		for each (Entity* r in raiders) 
		{
			if (r->getDistanceSquared(dragon) < closestDistance) 
			{
				closestDistance = r->getDistanceSquared(dragon);
				dragon->setTarget(r);
			}
		}
	}
	dragon->lookAt(dragon->getTarget());

	//Make Dragon follow Leader if alive
	dragon->getPhysicsNode()->setVelocity(Vector2(0, 0));
	
	if (dragonState)
	{
		if (leader->isAlive() && dragon->getDistanceSquared(leader) > pow(leader->getPhysicsNode()->getRadius() + dragon->getPhysicsNode()->getRadius(), 2))
		{
			float rot = dragon->getAngle(leader);
			rot *= PI / 180;
			Vector2 temp = Vector2(cos(rot), sin(rot));

			dragon->getPhysicsNode()->setVelocity(temp * dragon->getPhysicsNode()->getMaxSpeed());
		}
		else
		{
			float rot = dragon->getAngle(dragon->getTarget());
			rot *= PI / 180;
			Vector2 temp = Vector2(cos(rot), sin(rot));

			dragon->getPhysicsNode()->setVelocity(temp * dragon->getPhysicsNode()->getMaxSpeed());
		}
	}

	//Update Breath scale
	float shift = 0.1*msec;
	if (dragon->getDistanceSquared(dragon->getTarget()) < pow(dragon->getPhysicsNode()->getAggroRange(), 2)) 
	{
		if (breath->getPhysicsNode()->getXScale() > 100.0f)
		{
			breathState = 0;
			breath->getPhysicsNode()->setXScale(100.0f);
			breath->getPhysicsNode()->setYScale(50.0f);
			
		}
		else if (breath->getPhysicsNode()->getXScale() < 2.0f)
		{
			breathState = 1;
			breath->getPhysicsNode()->setXScale(2.0f);
			breath->getPhysicsNode()->setYScale(1.0f);
		}
		if (breathState == 1)
		{
			breath->getPhysicsNode()->updateXScale(1.5*shift);
			breath->getPhysicsNode()->updateYScale(0.75*shift);
		}
		else
		{
			breath->getPhysicsNode()->updateXScale(-2 * shift);
			breath->getPhysicsNode()->updateYScale(-shift);
		}
	}
	else if (breath->getPhysicsNode()->getXScale() > 0.0f) 
	{
		breath->getPhysicsNode()->updateXScale(-2 * shift);
		breath->getPhysicsNode()->updateYScale(-shift);
	}
	breath->getPhysicsNode()->setRadius(breath->getPhysicsNode()->getXScale());
}

void Physics::startGame() {
	//Move leader above map
	leader->getPhysicsNode()->setPosition(Vector3(0.0f, 0.0f, -199.0f));
	leader->getPhysicsNode()->setPosition(3, -12);
	leader->getPhysicsNode()->setRotation(90.0f);

	//Move raiders above map
	for (int i = 0; i < numRaiders; ++i) 
	{
		if (i % 2) 
		{
			raiders.at(i)->getPhysicsNode()->setPosition(Vector3(0.0f, 0.0f, -199.9f));
			raiders.at(i)->getPhysicsNode()->setPosition((i / 2) + 2, -14);
		}
		else 
		{
			raiders.at(i)->getPhysicsNode()->setPosition(Vector3(0.0f, 0.0f, -199.9f));
			raiders.at(i)->getPhysicsNode()->setPosition((i / 2) + 2, -13);
		}
	}


	//Move dragon above map
	dragon->getPhysicsNode()->setPosition(Vector3(0.0f, 0.0f, -199.5f));
	dragon->getPhysicsNode()->setPosition(16, 8);

	//Move breath to 50px to side of dragon
	breath->getPhysicsNode()->setPosition(Vector3(50.0f, 0.0f, -0.3f));

	//Start Game
	gameStart = !gameStart;
}
