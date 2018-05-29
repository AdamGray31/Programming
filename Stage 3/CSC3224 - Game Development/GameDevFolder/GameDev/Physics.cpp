#include "Physics.h"



Physics::Physics() 
{
	time = 0.0f;
}

bool Physics::updatePhysics(float msec, vector<Event>* events, vector<Entity*>* entities) 
{

	//If there are events in the queue, check the front of it
	if (!events->empty()) 
	{

		//Loop through each event in the queue
		int size = events->size();
		for(int i = 0; i < size; i++)
		{
			Event &currentEvent = events->at(i);
			//Loop through the systems in the event
			for (vector<Event::system>::iterator sysIt = currentEvent.systems.begin(); sysIt != currentEvent.systems.end(); ++sysIt) 
			{
				//If this system is on the systems queue, check type and act accordingly
				if (*sysIt == Event::physics) 
				{

					switch (currentEvent.eventType)
					{

					case Event::move:
					{
						//Move player
						entities->at(player)->setVelocity(currentEvent.data * 0.2f * msec);
						break;
					}
					case Event::aim:
					{
						//Aim
						float a = atan2(currentEvent.data.y, currentEvent.data.x) * 180 / System::Math::PI;
						entities->at(player)->setRotation(a);
						break;
					}
					case Event::fire:
					{
						//Fire bullet
						entities->at(playerShot)->setPosition(entities->at(player)->getPosition());
						entities->at(playerShot)->setRotation(entities->at(player)->getRotation());
						entities->at(playerShot)->setVelocity(Vector2(cos(entities->at(playerShot)->getRotation() / (180 / System::Math::PI)) * 0.5f * msec, sin(entities->at(playerShot)->getRotation() / (180 / System::Math::PI)) * 0.5f * msec));
						break;
					}
					case Event::grenadeThrow:
					{
						//Throw grenade
						entities->at(grenade)->setPosition(entities->at(player)->getPosition());
						entities->at(grenade)->setRotation(entities->at(player)->getRotation());
						entities->at(grenade)->setVelocity(Vector2(cos(entities->at(grenade)->getRotation() / (180 / System::Math::PI)) * 0.5f * msec, sin(entities->at(grenade)->getRotation() / (180 / System::Math::PI)) * 0.5f * msec));
						break;
					}
					case Event::explosion:
					{
						//Grenade explodes
						entities->at(grenade)->setVelocity(Vector2());
						break;
					}
					case Event::clearExplosion:
					{
						//Grenade resets
						entities->at(grenade)->setPosition(Vector2(-10000, -10000));
						break;
					}

					}

					//Remove self from systems
					currentEvent.systems.erase(sysIt);
					break;
				}
			}

			//If no more systems on the current event, erase it
			if (currentEvent.systems.empty()) 
			{
				events->erase(events->begin() + i);
				--i;
				size = events->size();
			}
		}
	}

	//Check bullet collision with enemy
	float distSq = 
		pow(entities->at(enemy)->getPosition().x - entities->at(playerShot)->getPosition().x, 2) +
		pow(entities->at(enemy)->getPosition().y - entities->at(playerShot)->getPosition().y, 2);
	float sumRadSq =
		pow(entities->at(enemy)->getRadius() + entities->at(playerShot)->getRadius(), 2);

	if (distSq < sumRadSq)
	{
		return true;
	}

	//Check grenade collision with enemy
	distSq =
		pow(entities->at(enemy)->getPosition().x - entities->at(grenade)->getPosition().x, 2) +
		pow(entities->at(enemy)->getPosition().y - entities->at(grenade)->getPosition().y, 2);
	sumRadSq =
		pow(entities->at(enemy)->getRadius() + entities->at(grenade)->getRadius(), 2);

	if (distSq < sumRadSq)
	{
		return true;
	}

	//Check player collision with enemy
	distSq =
		pow(entities->at(enemy)->getPosition().x - entities->at(player)->getPosition().x, 2) +
		pow(entities->at(enemy)->getPosition().y - entities->at(player)->getPosition().y, 2);
	sumRadSq =
		pow(entities->at(enemy)->getRadius() + entities->at(player)->getRadius(), 2);

	if (distSq < sumRadSq)
	{
		float p = entities->at(enemy)->getRadius() + entities->at(player)->getRadius() - sqrt(distSq);
		Vector2 normal = entities->at(enemy)->getPosition() - entities->at(player)->getPosition();
		normal.Normalise();
		entities->at(enemy)->setPosition(entities->at(enemy)->getPosition() + normal * p);
		entities->at(player)->setPosition(entities->at(player)->getPosition() - normal * p);
	}

	//Check collisions with walls
	for (int i = 5; i < 15; ++i)
	{
		//Check player collision with wall
		distSq =
			pow(entities->at(player)->getPosition().x - entities->at(i)->getPosition().x, 2) +
			pow(entities->at(player)->getPosition().y - entities->at(i)->getPosition().y, 2);
		sumRadSq =
			pow(entities->at(player)->getRadius() + entities->at(i)->getRadius(), 2);

		if (distSq < sumRadSq)
		{
			float p = entities->at(player)->getRadius() + entities->at(i)->getRadius() - sqrt(distSq);
			Vector2 normal = entities->at(player)->getPosition() - entities->at(i)->getPosition();
			normal.Normalise();
			entities->at(player)->setPosition(entities->at(player)->getPosition() + normal * p);
		}

		//Check enemy collision with wall
		distSq =
			pow(entities->at(enemy)->getPosition().x - entities->at(i)->getPosition().x, 2) +
			pow(entities->at(enemy)->getPosition().y - entities->at(i)->getPosition().y, 2);
		sumRadSq =
			pow(entities->at(enemy)->getRadius() + entities->at(i)->getRadius(), 2);

		if (distSq < sumRadSq)
		{
			float p = entities->at(enemy)->getRadius() + entities->at(i)->getRadius() - sqrt(distSq);
			Vector2 normal = entities->at(enemy)->getPosition() - entities->at(i)->getPosition();
			normal.Normalise();
			entities->at(enemy)->setPosition(entities->at(enemy)->getPosition() + normal * p);
		}


	}

	//Choose random new direction for enemy to move
	if (time > 100.0f)
	{
		time = 0.0f;
		float xDir = (rand() % 11 - 5);
		float yDir = (rand() % 11 - 5);
		entities->at(enemy)->setVelocity(Vector2(xDir * 0.05f * msec, yDir * 0.05f * msec));
	}
	
	//Loop through entities, updating positions based on their velocity and 
	for each (Entity* e in *entities)
	{
		e->updatePosition();
		
		//Bullet collisions
		if (e == entities->at(playerShot))
		{
			if (e->getPosition().x < -800.0f || e->getPosition().x > 800.0f || e->getPosition().y < -390.0f || e->getPosition().y > 590.0f)
			{
				e->setPosition(Vector2(-10000, -10000));
				e->setVelocity(Vector2());
			}

			for (int i = 5; i < 15; ++i)
			{
				//Check bullet collision with wall
				distSq =
					pow(e->getPosition().x - entities->at(i)->getPosition().x, 2) +
					pow(e->getPosition().y - entities->at(i)->getPosition().y, 2);
				sumRadSq =
					pow(e->getRadius() + entities->at(i)->getRadius(), 2);

				if (distSq < sumRadSq)
				{
					float penDepth = e->getRadius() + entities->at(i)->getRadius() - sqrt(distSq);
					Vector2 normalVector = e->getPosition() - entities->at(i)->getPosition();
					normalVector.Normalise();
					Vector2 contactPoint = e->getPosition() - normalVector * (e->getRadius() - penDepth);
					Vector2 velocitySum = e->getVelocity() - entities->at(i)->getVelocity();
					float normalVelocity = Vector2::Dot(velocitySum, normalVector);
					float epsilon = 1.5f;

					float J =
						(-(1 + epsilon) * normalVelocity) /
						(Vector2::Dot(normalVector, normalVector) * (2));

					e->setVelocity(e->getVelocity() + normalVector * 2 * J);	
				}
			}


		}
		//Grenade collisions
		else if (e == entities->at(grenade))
		{
			e->setVelocity(e->getVelocity() * 0.951f);

			if (e->getPosition().x < -800.0f || e->getPosition().x > 800.0f || e->getPosition().y < -390.0f || e->getPosition().y > 590.0f)
			{
				e->setVelocity(Vector2());
			}

			for (int i = 5; i < 15; ++i)
			{
				//Check grenade collision with wall
				distSq =
					pow(e->getPosition().x - entities->at(i)->getPosition().x, 2) +
					pow(e->getPosition().y - entities->at(i)->getPosition().y, 2);
				sumRadSq =
					pow(e->getRadius() + entities->at(i)->getRadius(), 2);

				if (distSq < sumRadSq)
				{
					float penDepth = e->getRadius() + entities->at(i)->getRadius() - sqrt(distSq);
					Vector2 normalVector = e->getPosition() - entities->at(i)->getPosition();
					normalVector.Normalise();
					Vector2 velocitySum = e->getVelocity() - entities->at(i)->getVelocity();
					float normalVelocity = Vector2::Dot(velocitySum, normalVector);
					float epsilon = 1.5f;

					float J =
						(-(1 + epsilon) * normalVelocity) /
						(Vector2::Dot(normalVector, normalVector) * (2));

					e->setVelocity(e->getVelocity() + normalVector * 2 * J);
				}
			}

		}
		//Outer wall collision
		else
		{
			if (e->getPosition().x < -800.0f)
			{
				e->setPosition(Vector2(-800.0f, e->getPosition().y));
			}
			if (e->getPosition().x > 800.0f)
			{
				e->setPosition(Vector2(800.0f, e->getPosition().y));
			}
			if (e->getPosition().y < -390.0f)
			{
				e->setPosition(Vector2(e->getPosition().x, -390.0f));
			}
			if (e->getPosition().y > 590.0f)
			{
				e->setPosition(Vector2(e->getPosition().x, 590.0f));
			}
		}
	}
	
	time += msec;

	return false;
}
