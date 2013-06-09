#include "Music.h"
#include "../lib/Info.h"
#include "../lib/Log.h"

std::list<Music*> Music::music;

Music::Music(music_t* mscxml)
{
	name = mscxml->ident();
	if(!msc.openFromFile(Info::getGameFolderName() + "music/" + mscxml->file()))
	{
		Log::log("Couldn't find " + Info::getGameFolderName() + "music/" + mscxml->file());
	}
	music.push_front(this);
}

void Music::play()
{
	msc.play();
}

void Music::pause()
{
	msc.pause();
}

void Music::stop()
{
	msc.stop();
}

void Music::setLoop(bool st)
{
	msc.setLoop(st);
}

bool Music::getLoop() const
{
	return msc.getLoop();
}

float Music::getDuration() const
{
	return msc.getDuration().asSeconds();
}

PE::Sound::Status Music::getStatus() const
{
	sf::Sound::Status st = msc.getStatus();
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

float Music::getCurrentPosition() const
{
	return msc.getPlayingOffset().asSeconds();
}

void Music::setCurrentPosition(float pos)
{
	msc.setPlayingOffset(sf::seconds(pos));
} 

void Music::setVolume(float vol)
{
	msc.setVolume(vol);
}

float Music::getVolume() const
{
	return msc.getVolume();
}

Music* Music::getMusic(std::string srchstr)
{
	std::list<Music*>::iterator it;
	for(it = music.begin(); it != music.end(); it++)
	{
		Music* m(*it);
		if(m->getName() == srchstr)
			return *it;
	}
	return NULL;
}

std::list<Music*>::iterator Music::getMusicIterator(std::string srchstr)
{
	std::list<Music*>::iterator it;
	for(it = music.begin(); it != music.end(); it++)
	{
		Music* m(*it);
		if(m->getName() == srchstr)
			return it;
	}
	return music.end();
}

std::string Music::getName() const
{
	return name;
}

Music::~Music()
{
	music.erase(Music::getMusicIterator(this->getName()));
}
