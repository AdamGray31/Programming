#pragma once

#include "Event.h"
#include "../inc/fmod.hpp"
#include <vector>

typedef FMOD::Sound* Sound;

class Audio 
{

	enum sounds 
	{
		music,
		shot,
		explode
	};

public:

	FMOD::System *m_pSystem;
	
	Audio(); 
	~Audio(); 

	void createSound(Sound* pSound, const char* pFile); 
	void playSound(Sound pSound, bool bLoop = false);
	void releaseSound(Sound pSound);
	void fillSoundbank();
	void update(vector<Event>* events);
	void stop();

private:

	std::vector<Sound> soundbank;

};