#include "../../nclgl/window.h"
#include "Renderer.h"
#include "Physics.h"
#include <stdlib.h>

#pragma comment(lib, "nclgl.lib")

int main() {
	Window w("CSC3222 Coursework", 1920, 1080);
	if (!w.HasInitialised()) {
		return -1;
	}

	Physics physics;
	Renderer renderer(w, &physics);
	
	if (!renderer.HasInitialised()) {
		return -1;
	}

	system("cls");
	cout
		<< "Controls:\n"
		<< "K	: Start game\n"
		<< "J	: Select random raider to path to Hoard\n"
		<< "L	: Select weakest raider to path to Pool\n"
		<< "UP	: Move Forwards\n"
		<< "DOWN	: Move Backwards\n"
		<< "LEFT	: Turn Left\n"
		<< "RIGHT	: Turn Right\n"
		<< "SPACE	: Fire Arrows\n"
		<< "\n\n"
		<< "Arrow cooldown: " << 0 << " seconds\n"
		<< "Leader HP:	" << 200 << "\n"
		<< "Dragon HP:	" << 1000 << "\n";

	for (int i = 0; i < physics.raiders.size(); ++i)
	{
		cout
			<< "Raider[" << i << "] HP:	" << physics.raiders.at(i)->getHP() << "\n";
	}

	while (w.UpdateWindow() && !(Window::GetKeyboard()->KeyDown(KEYBOARD_X) || Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE))) {
		float msec = w.GetTimer()->GetTimedMS();
		physics.UpdatePhysics(msec);
		renderer.UpdateScene(msec);
		renderer.RenderScene();
	}

	return 0;
}