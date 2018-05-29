#pragma once
#include <vector>
#include "../../nclgl/Vector2.h"

//Class to hold data about an event

using namespace std;

class Event {
	
public:

	enum type {
		move,
		fire,
		aim,
		grenadeThrow,
		explosion,
		clearExplosion
	};

	enum system {
		physics,
		audio,
		graphics,
		fileIO,
		input
	};

	const char* typeNames[6] = { "move", "fire", "aim", "grenadeThrow", "explosion", "clearExplosion"};
	const char* systemNames[5] = { "physics", "audio", "graphics", "fileIO", "input" };

	Event(type eventType, vector<system> systems, Vector2 data = Vector2(0, 0));
	type eventType;
	vector<system> systems;
	Vector2 data;

private:

};

