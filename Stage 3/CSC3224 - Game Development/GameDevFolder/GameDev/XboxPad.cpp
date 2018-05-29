#include "XboxPad.h"

XboxPad::XboxPad()  
{
}


XboxPad::~XboxPad() 
{

}

bool XboxPad::quit()
{
	return ((getState().Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
}

bool XboxPad::up() 
{
	return ((getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0) || (getState().Gamepad.sThumbLY / 32767.0 > 0.5);
}

bool XboxPad::down() 
{
	return ((getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0) || (getState().Gamepad.sThumbLY / 32767.0 < -0.5);
}

bool XboxPad::left() 
{
	return ((getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) || (getState().Gamepad.sThumbLX / 32767.0 < -0.5);
}

bool XboxPad::right() 
{
	return ((getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) || (getState().Gamepad.sThumbLX / 32767.0 > 0.5);
}

bool XboxPad::fire() 
{
	return ((float) getState().Gamepad.bRightTrigger / 255.0 > 0.5f);
}

bool XboxPad::throwGrenade()
{
	return ((float) getState().Gamepad.bLeftTrigger / 255.0 > 0.5f);
}

bool XboxPad::xboxConnected() 
{
	return XInputGetState(0, &state) == ERROR_SUCCESS;
}

Vector2 XboxPad::angle() 
{
	//Normalise axes
	float x = fmaxf(-1, (float) getState().Gamepad.sThumbRX / 32767.0);
	float y = fmaxf(-1, (float) getState().Gamepad.sThumbRY / 32767.0);
	//Deadzones
	float dzx = abs(x) < 0.1f ? 0 : x;
	float dzy = abs(y) < 0.1f ? 0 : y;

	return Vector2(dzx, dzy);
	
}

XINPUT_STATE XboxPad::getState() 
{

	ZeroMemory(&state, sizeof(XINPUT_STATE));

	XInputGetState(0, &state);

	return state;
}
