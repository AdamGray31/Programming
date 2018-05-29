#pragma once
#include "Controller.h"
#include "../../nclgl/Window.h"
#include "../../nclgl/Keyboard.h"
#include "../../nclgl/Mouse.h"

//Returns data about keyboard state

class KeyboardMouse :
	public Controller
{

public:
	KeyboardMouse();
	bool quit();
	bool up();
	bool down();
	bool left();
	bool right();
	bool fire();
	bool throwGrenade();
	Vector2 angle();
};

