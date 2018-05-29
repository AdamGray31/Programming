#include "Audio.h"

Audio::Audio() 
{
	//Create FMOD system object
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK) 
	{
		return;
	}

	//Get number of sound drivers in FMOD system
	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);
	if (driverCount == 0) 
	{
		return;
	}

	//Initialise system
	if (m_pSystem->init(64, FMOD_INIT_NORMAL, 0) != FMOD_OK) 
	{
		return;
	}

	//Fill soundbank with sounds
	fillSoundbank();

}

Audio::~Audio() 
{
	for (int i = 0; i < 3; ++i)
	{
		releaseSound(soundbank.at(i));
	}
	m_pSystem->release();
}

void Audio::createSound(Sound * pSound, const char * pFile) 
{
	m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
}

void Audio::playSound(Sound pSound, bool bLoop) 
{
	if (!bLoop) 
	{
		pSound->setMode(FMOD_LOOP_OFF);
	}
	else 
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	m_pSystem->playSound(pSound, nullptr, false, nullptr);

}

void Audio::releaseSound(Sound pSound) 
{
	pSound->release();
	
}

//Create sound objects and push them to the sound vector
void Audio::fillSoundbank() 
{

	Sound music;
	createSound(&music, "../sounds/music.mp3");
	soundbank.push_back(music);
	soundbank[sounds::music] = music;

	Sound gunshot;
	createSound(&gunshot, "../sounds/gunshot.wav");
	soundbank.push_back(gunshot);
	soundbank[sounds::shot] = gunshot;
	
	Sound explosion;
	createSound(&explosion, "../sounds/explosion.wav");
	soundbank.push_back(explosion);
	soundbank[sounds::explode] = explosion;

	//Start Music
	playSound(soundbank[sounds::music], true);
}

void Audio::update(vector<Event>* events) 
{
	m_pSystem->update();

	//If there are events in the queue, check the front of it
	if (!events->empty()) 
	 {
		
		//Loop through each event in the queue
		int size = events->size();
		for(int i = 0; i < size; ++i) 
		{
			Event &currentEvent = events->at(i);
			//Loop through the systems in the event
			for (vector<Event::system>::iterator sysIt = currentEvent.systems.begin(); sysIt != currentEvent.systems.end(); ++sysIt) 
			{
				//If this system is on the systems queue(vector), check type and act accordingly
				if (*sysIt == Event::audio) 
				{
					switch (currentEvent.eventType) 
					{

					case Event::fire:
					{
						playSound(soundbank[shot], false);
						break;
					}

					case Event::explosion:
					{
						playSound(soundbank[explode], false);
						break;
					}

					}


					//Remove self from systems
					currentEvent.systems.erase(sysIt);
					break;
				}
			}

			//If no more systems on the current event, erase it
			if (currentEvent.systems.empty()) 
			{
				events->erase(events->begin() + i);
				i--;
				size = events->size();
			}
		}
	}


}

void Audio::stop()
{
	for (auto s : soundbank)
	{
		s->release();
	}
}