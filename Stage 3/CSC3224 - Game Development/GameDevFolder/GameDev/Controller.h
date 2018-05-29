#pragma once
#include "../../nclgl/Vector2.h"

//Virtual class for XboxPad and KBM to inherit from

class Controller
{
public:
	Controller();
	virtual ~Controller() = 0;
	virtual bool quit();
	virtual bool up();
	virtual bool down();
	virtual bool right();
	virtual bool left();
	virtual bool fire();
	virtual bool throwGrenade();
	virtual bool xboxConnected();
	virtual Vector2 angle();
};

