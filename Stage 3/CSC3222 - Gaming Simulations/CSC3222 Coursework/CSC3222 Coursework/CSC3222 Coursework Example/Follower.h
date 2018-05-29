#pragma once
#include "Entity.h"
class Follower :
	public Entity
{

	enum task 
	{
		pool,
		hoard
	};

public:
	Follower();
	Follower(PhysicsNode *p);
	~Follower();
	void changeDamage(int d);
	void setTask(bool doingTask, int task);
	int getDamage() const;
	bool isDoingTask() const;
	int getTask() const;

private:

	int damage;
	bool doingTask;
	int currentTask;

};

