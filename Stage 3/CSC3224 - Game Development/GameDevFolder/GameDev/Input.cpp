#include "Input.h"

Input::Input() 
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	xbox = new XboxPad();
	kbm = new KeyboardMouse();

	if (XInputGetState(0, &state) == ERROR_SUCCESS) 
	{
		controller = xbox;
		usingController = true;
	}
	else 
	{
		controller = kbm;
		usingController = false;
	}

	fired = false;
	thrown = false;
	exploded = false;
	bulletCooldown = 2000.0f;
	grenadeCooldown = 4000.0f;
}

Input::~Input() 
{
	delete kbm, xbox;
	controller = xbox = kbm = nullptr;
}

bool Input::getInputs(float msec, vector<Event> *events)
{

	//Controller disconnects
	if (usingController && !xbox->xboxConnected()) 
	{
		cout << "Please plug the controller back in!\n";
		while (usingController && !xbox->xboxConnected()) 
		{
			//Halt program
		}
	}

	//Create movement event
	Vector2 movementDirection = Vector2();
	if (controller->up()) 
	{
		movementDirection = movementDirection + Vector2(0, 1.0f);
	}
	if (controller->down()) 
	{
		movementDirection = movementDirection + Vector2(0, -1.0f);
	}
	if (controller->left()) 
	{
		movementDirection = movementDirection + Vector2(-1.0f, 0);
	}
	if (controller->right()) 
	{
		movementDirection = movementDirection + Vector2(1.0f, 0);
		
	}
	movementDirection.Normalise();
	events->push_back(Event(Event::move, vector<Event::system>({ Event::physics }), movementDirection));

	//Create fire event
	if (controller->fire() && !fired) 
	{
		fired = true;
		events->push_back(Event(Event::fire, vector<Event::system>({ Event::physics , Event::audio })));
	}

	if (fired)
	{
		bulletCooldown -= msec;
	}

	if (bulletCooldown < 0.0f) {
		bulletCooldown = 2000.0f;
		fired = false;
	}

	//Create grenadeThrow event
	if (controller->throwGrenade() && !thrown)
	{
		thrown = true;
		events->push_back(Event(Event::grenadeThrow, vector<Event::system>({ Event::physics, Event::graphics, Event::audio })));
	}

	if (thrown)
	{
		grenadeCooldown -= msec;
	}

	if (grenadeCooldown < 3000.0f && !exploded)
	{
		exploded = true;
		events->push_back(Event(Event::explosion, vector<Event::system>({ Event::physics, Event::graphics, Event::audio })));
	}

	if (grenadeCooldown < 0.0f)
	{
		events->push_back(Event(Event::clearExplosion, vector<Event::system>({ Event::physics })));
		grenadeCooldown = 4000.0f;
		thrown = false;
		exploded = false;
	}

	//Create aim event
	Vector2 a = controller->angle();
	if (a != Vector2(0, 0)) 
	{
		events->push_back(Event(Event::aim, vector<Event::system>({ Event::physics }), a));
	}

	if (controller->quit())
	{
		return false;
	}

	return true;
}

Controller *Input::getController()
{
	return controller;
}
