#include "KeyboardMouse.h"



KeyboardMouse::KeyboardMouse() 
{
}

bool KeyboardMouse::quit()
{
	return (Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE));
}

bool KeyboardMouse::up() 
{
	return (Window::GetKeyboard()->KeyDown(KEYBOARD_W) || Window::GetKeyboard()->KeyDown(KEYBOARD_UP));
}

bool KeyboardMouse::down() 
{
	return (Window::GetKeyboard()->KeyDown(KEYBOARD_S) || Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN));
}

bool KeyboardMouse::left() 
{
	return (Window::GetKeyboard()->KeyDown(KEYBOARD_A) || Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT));
}

bool KeyboardMouse::right() 
{
	return (Window::GetKeyboard()->KeyDown(KEYBOARD_D) || Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT));
}

bool KeyboardMouse::fire()
{
	return (Window::GetMouse()->ButtonDown(MOUSE_LEFT));
}

bool KeyboardMouse::throwGrenade()
{
	return (Window::GetMouse()->ButtonDown(MOUSE_RIGHT));
}

Vector2 KeyboardMouse::angle()
{
	Vector2 dir = Window::GetMouse()->GetRelativePosition();
	return Vector2(dir.x, -dir.y);
}
