#include <vector>
#include "../../nclgl/Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Physics.h"
#include "Event.h"
#include "Entity.h"
#include "Audio.h"
#include "FileIO.h"

#pragma comment(lib, "nclgl.lib")

using namespace std;



int main() 
{
	//Vectors for events and entities
	vector<Event>* eventVector = new vector<Event>;
	vector<Entity*>* entities = new vector<Entity*>;
	
	//Initialise gameWindow
	Window gameWindow("Top Down Shooter", 1920, 1080, false);
	if (!gameWindow.HasInitialised()) 
	{
		return -1;
	}

	//gameWindow.LockMouseToWindow(true);
	//gameWindow.ShowOSPointer(false);

	//Initialise subsystems
	FileIO io(entities);
	Physics physics;
	Renderer renderer(gameWindow, entities);
	if (!renderer.HasInitialised()) 
	{
		return -1;
	}
	Audio audio;
	Input input;

	//Profiling variables
	float timeSinceProfile = 0.0f;
	int framerate = 0;
	float inputTime = 0.0f;
	float physicsTime = 0.0f;
	float rendererTime = 0.0f;
	float audioTime = 0.0f;

	int level = 1;

	while (gameWindow.UpdateWindow() && level < 4) 
	{

		float msec = gameWindow.GetTimer()->GetTimedMS();
		float currentTime = gameWindow.GetTimer()->GetMS();

		//If user presses quit buttons, exit loop
		if (!input.getInputs(msec, eventVector))
		{
			break;
		}
		inputTime += gameWindow.GetTimer()->GetMS() - currentTime;

		//If physics.update returns true, load next level
		currentTime = gameWindow.GetTimer()->GetMS();
		if (physics.updatePhysics(msec, eventVector, entities))
		{
			io.nextLevel();
			++level;
			continue;
		}
		physicsTime += gameWindow.GetTimer()->GetMS() - currentTime;

		//render the scene
		currentTime = gameWindow.GetTimer()->GetMS();
		renderer.UpdateScene(msec, eventVector);
		renderer.RenderScene();
		rendererTime += gameWindow.GetTimer()->GetMS() - currentTime;

		//Play any audio
		currentTime = gameWindow.GetTimer()->GetMS();
		audio.update(eventVector);
		audioTime += gameWindow.GetTimer()->GetMS() - currentTime;

		//Display profiling and controls once per second
		timeSinceProfile += msec;
		framerate++;
		if (timeSinceProfile >= 1000.0f)
		{

			system("cls");
			if (framerate)
			{
				cout
					<< "Framerate	: " << framerate << "	fps\n"
					<< "\n"
					<< "Average frame times:\n"
					<< "Input		: " << inputTime / framerate << "	ms\n"
					<< "Physics		: " << physicsTime / framerate << "	ms\n"
					<< "Renderer	: " << rendererTime / framerate << "	ms\n"
					<< "Audio		: " << audioTime / framerate << "	ms\n"
					<< "\nLevel		: " << level << "\n"
					<< "\n\n";
				if (input.usingController)
				{
					cout
						<< "Controls:\n"
						<< "Left stick	: Move\n"
						<< "Right stick	: Aim\n"
						<< "Right trigger	: Fire\n"
						<< "Left trigger	: Throw Grenade\n"
						<< "Start		: Quit\n";
				}else
				{
					cout
						<< "Controls:\n"
						<< "WASD		: Move\n"
						<< "Mouse		: Aim\n"
						<< "LMB		: Fire\n"
						<< "RMB		: Throw Grenade\n"
						<< "Escape		: Quit\n";
				}
			}

			//Reset profiling variables
			inputTime = 0.0f;
			physicsTime = 0.0f;
			rendererTime = 0.0f;
			audioTime = 0.0f;

			timeSinceProfile = 0.0f;
			framerate = 0;
		}

	}

	audio.stop();

	delete eventVector;
	entities->clear();

	cout << "\n\nGame over! You " << ((level==4) ? "win!" : "lose!") << "\nType any char to exit:";
	int x;
	cin >> x;

	return 0;
}

