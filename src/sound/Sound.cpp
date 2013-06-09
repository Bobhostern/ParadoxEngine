#include "Sound.h"
#include "../lib/Info.h"
#include "../lib/Log.h"

std::list<Sound*> Sound::sounds;

Sound::Sound(music_t* mscxml)
{
	name = mscxml->ident();
	if(!sndbf.loadFromFile(Info::getGameFolderName() + "music/" + mscxml->file()))
	{
		Log::log("Couldn't find " + Info::getGameFolderName() + "music/" + mscxml->file());
	}
	snd = new sf::Sound(sndbf);
	sounds.push_front(this);
}

void Sound::play()
{
	snd->play();
}

void Sound::pause()
{
	snd->pause();
}

void Sound::stop()
{
	snd->stop();
}

void Sound::setLoop(bool st)
{
	snd->setLoop(st);
}

bool Sound::getLoop() const
{
	return snd->getLoop();
}

float Sound::getDuration() const
{
	return sndbf.getDuration().asSeconds();
}

PE::Sound::Status Sound::getStatus() const
{
	sf::Sound::Status st = snd->getStatus();
	switch(st)
	{
		case sf::Sound::Playing:
			return PE::Sound::PLAYING;
		case sf::Sound::Paused:
			return PE::Sound::PAUSED;
		case sf::Sound::Stopped:
			return PE::Sound::STOPPED;
	}
}

float Sound::getCurrentPosition() const
{
	return snd->getPlayingOffset().asSeconds();
}

void Sound::setCurrentPosition(float pos)
{
	snd->setPlayingOffset(sf::seconds(pos));
} 

void Sound::setVolume(float vol)
{
	snd->setVolume(vol);
}

float Sound::getVolume() const
{
	return snd->getVolume();
}

Sound* Sound::getSound(std::string srchstr)
{
	std::list<Sound*>::iterator it;
	for(it = sounds.begin(); it != sounds.end(); it++)
	{
		Sound* m(*it);
		if(m->getName() == srchstr)
			return *it;
	}
	return NULL;
}

std::list<Sound*>::iterator Sound::getSoundIterator(std::string srchstr)
{
	std::list<Sound*>::iterator it;
	for(it = sounds.begin(); it != sounds.end(); it++)
	{
		Sound* s(*it);
		if(s->getName() == srchstr)
			return it;
	}
	return sounds.end();
}

std::string Sound::getName() const
{
	return name;
}

Sound::~Sound()
{
	delete snd;
	sounds.erase(Sound::getSoundIterator(this->getName()));
}
