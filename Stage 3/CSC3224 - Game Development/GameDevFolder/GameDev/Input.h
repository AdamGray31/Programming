#pragma once
#include "../../nclgl/Window.h"
#include "Event.h"
#include "Entity.h"
#include "Controller.h"
#include "KeyboardMouse.h"
#include "XboxPad.h"
#include <vector>

//Class with a controller pointer that interprets input

class Input 
{

public:

	Input();
	~Input();
	bool getInputs(float msec, vector<Event> *events);
	Controller* getController();

	bool usingController;

private:

	Controller *controller;
	Controller *xbox;
	Controller *kbm;
	
	bool fired;
	bool thrown;
	bool exploded;
	float bulletCooldown;
	float grenadeCooldown;
};

