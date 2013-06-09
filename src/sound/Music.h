#ifndef __MUSIC_H_
#define __MUSIC_H_

#include <SFML/Audio.hpp>
#include <list>
#include "../xsd/music.h"
#include "../lib/stringh.h"
#include "soundlib.h"

class Music
{
	public:
		Music(music_t*);
		void play();
		void pause();
		void stop();
		void setLoop(bool);
		bool getLoop() const;
		float getDuration() const;
		PE::Sound::Status getStatus() const;
		float getCurrentPosition() const;
		void setCurrentPosition(float);
		void setVolume(float);
		float getVolume() const;
		std::string getName() const;
		static Music* getMusic(std::string);
		static std::list<Music*>::iterator getMusicIterator(std::string);
		virtual ~Music();
	private:
		std::string name;
		sf::Music msc;
		static std::list<Music*> music;
};

#endif // __MUSIC_H_
