#include "Physics.h"



Physics::Physics()
{

	numEntities = 17;
	numRaiders = 15;
	numRocks = 9;

	leader = new Leader(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, RAIDERRADIUS,  0.0f, Vector3(10.0f, 10.0f, 1.0f)));
	leader->getPhysicsNode()->setMaxSpeed(RAIDERVELOCITY);
	entities.push_back(leader);

	for (int i = 0; i < numRaiders; i++)
	{
		raiders.push_back(new Follower(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, RAIDERRADIUS, 0.0f, Vector3(10.0f, 10.0f, 1.0f))));
		raiders.at(i)->getPhysicsNode()->setMaxSpeed(RAIDERVELOCITY);
		entities.push_back(raiders.at(i));
	}

	rocks.push_back(new Entity(new PhysicsNode(Vector3(47.41f, -201.39f, 0.0f), 0.0f, 0.75f * GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));
	rocks.push_back(new Entity(new PhysicsNode(Vector3(-167.68f, -281.90f, 0.0f), 0.0f, 0.75f * GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));
	rocks.push_back(new Entity(new PhysicsNode(Vector3(-275.33f, -328.21f, 0.0f), 0.0f, GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));
	rocks.push_back(new Entity(new PhysicsNode(Vector3(-586.27f, -81.71f, 0.0f), 0.0f, 2 * GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));
	rocks.push_back(new Entity(new PhysicsNode(Vector3(-542.51f, 198.62f, 0.0f), 0.0f, 2 * GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));
	rocks.push_back(new Entity(new PhysicsNode(Vector3(-80.48f, 267.26f, 0.0f), 0.0f, 2 * GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));
	rocks.push_back(new Entity(new PhysicsNode(Vector3(105.44f, 367.33f, 0.0f), 0.0f, 2 * GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));
	rocks.push_back(new Entity(new PhysicsNode(Vector3(499.93f, 364.74f, 0.0f), 0.0f, 1.5f * GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));
	rocks.push_back(new Entity(new PhysicsNode(Vector3(152.89f, 38.73f, 0.0f), 0.0f, GRIDSQUARE, 0.0f, Vector3(1.0f, 1.0f, 1.0f))));

	map = new Entity(new PhysicsNode(Vector3(0.0f, 100.0f, -200.0f), 0.0f, -1.0f, 0.0f, Vector3(864.0f, 540.0f, 100.0f)));

	dragon = new Dragon(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, DRAGONRADIUS, 4*GRIDSQUARE, Vector3(50.0f, 50.0f, 1.0f)));
	entities.push_back(dragon);
	dragon->getPhysicsNode()->setMaxSpeed(DRAGONVELOCITY);
	dragonState = 1;

	breath = new Entity(new PhysicsNode(Vector3(0.0f, 0.0f, -300.0f), 0.0f, GRIDSQUARE, 0.0f, Vector3(2.0f, 1.0f, 1.0f)));
	breathState = 1;
	
}

Physics::~Physics()
{
	raiders.clear();
	entities.clear();
	rocks.clear();
}

void Physics::UpdatePhysics(float msec)
{
	
	//Game Start
	if (Window::GetKeyboard()->Keyboard::KeyTriggered(KEYBOARD_K) && !gameStart && !aiDemo) {

		startGame();

	}
	
	//Launch Coursework 1 Physics System
	if (gameStart) {

		moveLeader(msec);
	
		updateRaiders(msec);

		updateDragon(msec);

		collisionDetection(msec);

		for each (Entity* e in entities) {
			e->getPhysicsNode()->updatePosition(Vector3(e->getPhysicsNode()->getVelocity().x, e->getPhysicsNode()->getVelocity().y, 0));
		}
		
	}


}

void Physics::collisionDetection(float msec) {

	//Loop through entities and check their collisions
	for each(Entity* e1 in entities) {
		//Check Entity-Entity collision
		for each(Entity* e2 in entities) {
			if (e1 == e2) { continue; }
			float distSq = e1->getDistanceSquared(e2);
			float radSum = pow(e1->getPhysicsNode()->getRadius() + e2->getPhysicsNode()->getRadius(), 2);
			if (distSq < radSum) {

				collisionResponse(msec, e1, e2);
				
				if (e1 != leader) {
					//e1->moveAway(e2, msec);
				}
				if (e2 != leader) {
					//e2->moveAway(e1, msec);
				}
				break;
			}
		}
		//Check Entity-Rock collisions
		for each(Entity* r in rocks) {
			float distSq = e1->getDistanceSquared(r);
			float radSum = pow(e1->getPhysicsNode()->getRadius() + r->getPhysicsNode()->getRadius(), 2);
			if (distSq < radSum) {

				e1->moveAway(r, msec);
				
				//collisionResponse(e1, r);
				
			}
		}
	}
}

//Fix response 

void Physics::collisionResponse(float msec, Entity* e1, Entity*e2) {

	float p = e1->getPhysicsNode()->getRadius() + e2->getPhysicsNode()->getRadius() - pow(e1->getDistanceSquared(e2), 0.5f);
	Vector3 N = e1->getPhysicsNode()->getPosition() - e2->getPhysicsNode()->getPosition();
	Vector3 P = e1->getPhysicsNode()->getPosition() - N * (e1->getPhysicsNode()->getRadius() - p);

	Vector3 vAB = Vector3(e1->getPhysicsNode()->getVelocity().x - e2->getPhysicsNode()->getVelocity().x, e1->getPhysicsNode()->getVelocity().y - e2->getPhysicsNode()->getVelocity().y, 0);
	float vN = Vector3::Dot(vAB, N);

	float J = -((1 + 0.8)*vN) / (Vector3::Dot(N, N*(1 / 1.0f + 1 / 1.5f)));

	Vector2 e1NewV = Vector2(e1->getPhysicsNode()->getVelocity().x * J*N.x, e1->getPhysicsNode()->getVelocity().y + J * N.y);

	if (e1 != leader) {
		e1->getPhysicsNode()->setVelocity(e1NewV);
	}

	Vector2 e2NewV = Vector2(e2->getPhysicsNode()->getVelocity().x - J * N.x, e2->getPhysicsNode()->getVelocity().y - J * N.y);
	
	if (e2 != leader) {
		e2->getPhysicsNode()->setVelocity(e2NewV);
	}
	
}

void Physics::moveLeader(float msec) {
	//Leader Rotation
	float shift = LEADERROT * msec;
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT)) {
		leader->getPhysicsNode()->updateRotation(shift);
	}
	else if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT)) {
		leader->getPhysicsNode()->updateRotation(-shift);
	}

	//Leader Translation
	leader->getPhysicsNode()->setVelocity(Vector2(0, 0));
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_UP)) {
		float rot = leader->getPhysicsNode()->getRotation();
		rot *= PI / 180;
		Vector2 temp = Vector2(cos(rot), sin(rot));

		leader->getPhysicsNode()->setVelocity(Vector2(temp.x * leader->getPhysicsNode()->getMaxSpeed() * msec, temp.y * leader->getPhysicsNode()->getMaxSpeed() * msec));
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN)) {
		float rot = leader->getPhysicsNode()->getRotation();
		rot *= PI / 180;
		Vector2 temp = Vector2(cos(rot), sin(rot));

		leader->getPhysicsNode()->setVelocity(Vector2(-temp.x * leader->getPhysicsNode()->getMaxSpeed() * msec, -temp.y * leader->getPhysicsNode()->getMaxSpeed() * msec));
	}
}

void Physics::updateRaiders(float msec) {

	//Launch raiders' arrows
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
		//Launch arrows
	}

	//Raider manipulation
	int raidersInRange = 0;

	for (int i = 0; i < numRaiders; i++) {

		
		//Rotate raiders
		raiders.at(i)->lookAt(dragon);

		//Count raiders within range of the dragon, set nearest as target
		if (raiders.at(i)->getDistanceSquared(dragon) <= pow(dragon->getPhysicsNode()->getAggroRange(), 2)) {
			if (dragon->getTarget() == leader) {
				dragon->setTarget(raiders.at(i));
			}
			++raidersInRange;
		}

		//Make raiders follow Leader
		float distL = leader->getDistanceSquared(raiders.at(i));
		if (distL > pow(leader->getPhysicsNode()->getRadius() + raiders.at(i)->getPhysicsNode()->getRadius(), 2)) {
			float rot = raiders.at(i)->getAngle(leader);
			rot *= PI / 180;
			Vector2 temp = Vector2(cos(rot), sin(rot));

			raiders.at(i)->getPhysicsNode()->setVelocity(Vector2(temp.x * raiders.at(i)->getPhysicsNode()->getMaxSpeed() * msec, temp.y * raiders.at(i)->getPhysicsNode()->getMaxSpeed() * msec));
		}
	}
	dragon->getPhysicsNode()->updateEntitiesInRange(raidersInRange);

}

void Physics::updateDragon(float msec) {
	
	//If no raiders are within range, target the leader
	if (!dragon->getPhysicsNode()->getEntitiesInRange()) {
		dragon->setTarget(leader);
	}
	dragon->lookAt(dragon->getTarget());

	//Make Dragon follow Leader
	dragon->getPhysicsNode()->setVelocity(Vector2(0, 0));
	if (Window::GetKeyboard()->Keyboard::KeyTriggered(KEYBOARD_D)) {
		dragonState = !dragonState;
	}
	if (dragonState && dragon->getDistanceSquared(leader) > pow(leader->getPhysicsNode()->getRadius() + dragon->getPhysicsNode()->getRadius(), 2)) {
		float rot = dragon->getAngle(leader);
		rot *= PI / 180;
		Vector2 temp = Vector2(cos(rot), sin(rot));

		dragon->getPhysicsNode()->setVelocity(Vector2(temp.x * dragon->getPhysicsNode()->getMaxSpeed() * msec, temp.y * dragon->getPhysicsNode()->getMaxSpeed() * msec));
	}
	//Update Breath scale
	float shift = 0.1*msec;
	if (dragon->getDistanceSquared(dragon->getTarget()) < pow(dragon->getPhysicsNode()->getAggroRange(), 2)) {
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
	else if (breath->getPhysicsNode()->getXScale() > 0.0f) {
		breath->getPhysicsNode()->updateXScale(-2 * shift);
		breath->getPhysicsNode()->updateYScale(-shift);
	}
}

void Physics::startGame() {
	//Move leader above map
	leader->getPhysicsNode()->setPosition(Vector3(0.0f, 0.0f, -199.0f));
	leader->getPhysicsNode()->setPosition(3, -12);
	leader->getPhysicsNode()->setRotation(90.0f);

	//Move raiders above map
	for (int i = 0; i < numRaiders; ++i) {
		if (i % 2) {
			raiders.at(i)->getPhysicsNode()->setPosition(Vector3(0.0f, 0.0f, -199.9f));
			raiders.at(i)->getPhysicsNode()->setPosition((i / 2) + 2, -14);
		}
		else {
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
