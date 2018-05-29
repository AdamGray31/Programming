#include "Entity.h"

bool compareNodes(Node* a, Node* b)
{
	if (a->getF() == b->getF())
	{
		return a->getH() > b->getH();
	}
	return a->getF() > b->getF();
}

Entity::Entity()
{
	physicsNode = new PhysicsNode();
}

Entity::Entity(PhysicsNode *p):
	physicsNode(p)
{
}

Entity::~Entity() 
{
	delete physicsNode;

	physicsNode = nullptr;
}

void Entity::setPhysicsNode(PhysicsNode *p) 
{
	physicsNode = p;
}

void Entity::lookAt(Entity *b) 
{
	physicsNode->setRotation(getAngle(b));
}

void Entity::moveTowards(Entity *b, float msec) 
{
	float rot = getAngle(b);
	rot *= PI / 180;
	Vector2 temp = Vector2(cos(rot), sin(rot));

	physicsNode->setVelocity(Vector2(temp.x * physicsNode->getMaxSpeed() * msec, temp.y * physicsNode->getMaxSpeed() * msec));
}

void Entity::moveAway(Entity *b, float msec) 
{
	float rot = getAngle(b);
	rot *= PI / 180;
	Vector2 temp = Vector2(cos(rot), sin(rot));

	physicsNode->setVelocity(Vector2(-temp.x * physicsNode->getMaxSpeed(), -temp.y * physicsNode->getMaxSpeed()));
}

void Entity::moveForwards(float msec) 
{
	float rot = physicsNode->getRotation();
	rot *= PI / 180;
	Vector2 temp = Vector2(cos(rot), sin(rot));

	physicsNode->setVelocity(Vector2(temp.x * physicsNode->getMaxSpeed() * msec, temp.y * physicsNode->getMaxSpeed() * msec));
}

void Entity::moveBackwards(float msec) 
{
	float rot = physicsNode->getRotation();
	rot *= PI / 180;
	Vector2 temp = Vector2(cos(rot), sin(rot));

	physicsNode->setVelocity(Vector2(-temp.x * physicsNode->getMaxSpeed() * msec, -temp.y * physicsNode->getMaxSpeed() * msec));

}

void Entity::setMass(float m) 
{
	mass = m;
}

void Entity::setHP(float hp) 
{
	hitPoints = hp;
}

void Entity::updateHP(float hp) 
{
	hitPoints += hp;
	if (hitPoints > maxHP) 
	{
		hitPoints = maxHP;
	}
}

void Entity::setMaxHP(float hp) 
{
	maxHP = hp;
}


//Very inefficient and incorrect
void Entity::pathTo(Node* startNode, Node* goalNode)
{
	//Initialise lists
	std::vector<Node*> openList;
	std::vector<Node*> closedList;

	bool reachedGoal = false;
	bool solved = false;

	//Add startnode to openList
	startNode->setG(0);
	startNode->setH(*startNode, *goalNode);
	startNode->setF();
	openList.push_back(startNode);

	while (!reachedGoal)
	{
		
		//Select lowest cost node from open list
		Node* p = nullptr;
		int lowestF = 100000;
		for (auto it : openList)
		{
			if (it->getF() < lowestF)
			{
				lowestF = it->getF();
				p = it;
			}
		}
		
		//If current node is the goal, add it to the closed list and continue
		if (p->getX() == goalNode->getX() && p->getY() == goalNode->getY())
		{
			closedList.push_back(p);
			for (int i = 0; i < openList.size(); ++i)
			{
				if (openList.at(i)->getX() == p->getX() && openList.at(i)->getY() == p->getY())
				{
					openList.erase(openList.begin() + i);
				}
			}
			reachedGoal = true;
			solved = true;
		}
		//Else if current node is null, no path has been found, exit
		else if (p == nullptr)
		{
			reachedGoal = true;
		}
		//Otherwise, add the node to the closed list, remove it from the openlist, and search its neighbours
		else
		{
			//Add to closed, remove from open
			closedList.push_back(p);
			for (int i = 0; i < openList.size(); ++i)
			{
				if (openList.at(i)->getX() == p->getX() && openList.at(i)->getY() == p->getY())
				{
					openList.erase(openList.begin() + i);
				}
			}

			//Search neighbours
			for (int i = 0; i < p->getConnectedNodes().size(); ++i)
			{
				Node* q = p->getConnectedNodes().at(i);

				//Get cost of neighbours
				int cost = 0;
				if (abs(q->getX() - p->getX()) > 0 && abs(q->getY() - p->getY()) > 0)
				{
					cost = p->getG() + 15;
				}
				else
				{
					cost = p->getG() + 10;
				}
				int qG = cost;

				int qH = 0;
				int dx = abs(q->getX() - goalNode->getX());
				int dy = abs(q->getY() - goalNode->getY());
				while (dx > 0 || dy > 0)
				{
					if (dx > 0 && dy > 0)
					{
						qH += 15;
						--dx;
						--dy;
					}
					else if (dx > 0)
					{
						qH += 10;
						--dx;
					}
					else if (dy > 0)
					{
						qH += 10;
						--dy;
					}
				}

				int qF = qG + qH;
				
				//Check if neighbour is in either list
				bool inOpen = false;
				bool inClosed = false;

				for each (Node* n in openList)
				{
					if (q->getX() == n->getX() && q->getY() == n->getY())
					{
						inOpen = true;
						break;
					}
				}
				for each (Node* n in closedList)
				{
					if (q->getX() == n->getX() && q->getY() == n->getY())
					{
						inClosed = true;
						break;
					}
				}

				//If it is in either list, and it's cheaper to get to it from the current node, set its new costs and its new parent
				if (inOpen || inClosed)
				{
					if (qG <= q->getG())
					{
						q->setG(qG);
						q->setF();
						q->setParent(p);
					}
				}
				//Otherwise, add it to the openList, and set its parent
				else
				{
					q->setG(qG);
					q->setH(*q, *goalNode);
					q->setF();
					q->setParent(p);
					openList.push_back(q);
				}
			}
		}
	}

	//If the path has been completed, have the Entity follow it (Non-functional)
	if (solved)
	{
		std::vector<Node*> path;
		Node* toAdd = closedList.back();
		while (toAdd != startNode)
		{
			path.push_back(toAdd);
			toAdd = toAdd->getParent();
		}
		
		openList.clear();
		closedList.clear();
	
		Vector2 nodePos = Vector2(path.at(0)->getX() * 26.66f + 12.0f, (path.at(0)->getY() * 26.66f - 2.0f));
		float angle = atan2(
			nodePos.y - physicsNode->getY(),
			nodePos.x - physicsNode->getX());
		Vector2 v = Vector2(cos(angle), sin(angle));
		physicsNode->setVelocity(v * physicsNode->getMaxSpeed());
	}
	else
	{
		openList.clear();
		closedList.clear();
	}

}

float Entity::getAngle(Entity *b) const 
{
	return atan2(
		b->getPhysicsNode()->getY() - physicsNode->getY(),
		b->getPhysicsNode()->getX() - physicsNode->getX())
		* (180 / PI);
}

float Entity::getDistanceSquared(Entity *b) const
{
	return 
		pow(b->getPhysicsNode()->getX() - physicsNode->getX(), 2) +
		pow(b->getPhysicsNode()->getY() - physicsNode->getY(), 2);
}

float Entity::getMass() const 
{
	return mass;
}

float Entity::getHP() const
{
	return hitPoints;
}

float Entity::getMaxHP() const 
{
	return maxHP;
}

bool Entity::isAlive() const
{
	return getHP() > 0.0f;
}

PhysicsNode* Entity::getPhysicsNode() 
{
	return physicsNode;
}
