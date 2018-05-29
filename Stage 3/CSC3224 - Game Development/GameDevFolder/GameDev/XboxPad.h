#pragma once
#include "Controller.h"
#include <Windows.h>
#include <Xinput.h>

//Returns state of xbox controller

class XboxPad :
	public Controller
{
public:
	XboxPad();
	~XboxPad();
	bool quit();
	bool up();
	bool down();
	bool left();
	bool right();
	bool fire();
	bool throwGrenade();
	bool xboxConnected();
	Vector2 angle();
	XINPUT_STATE getState();
private:
	XINPUT_STATE state;
};

