#include "../../nclgl/window.h"
#include "Renderer.h"
#include "Physics.h"

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

	//w.LockMouseToWindow(true);
	//w.ShowOSPointer(false);

	cout << 
		"\n\n" <<
		"Controls:\n" <<
		"K	: Start game\n" <<
		"UP	: Move Forwards\n" <<
		"DOWN	: Move Backwards\n" <<
		"LEFT	: Turn Left\n" <<
		"RIGHT	: Turn Right\n";

	while (w.UpdateWindow() && !(Window::GetKeyboard()->KeyDown(KEYBOARD_X) || Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE))) {
		float msec = w.GetTimer()->GetTimedMS();
		physics.UpdatePhysics(msec);
		renderer.UpdateScene(msec);
		renderer.RenderScene();
	}

	return 0;
}