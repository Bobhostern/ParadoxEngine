#ifndef __SOUND_H_
#define __SOUND_H_

#include <SFML/Audio.hpp>
#include <list>
#include "../xsd/music.h"
#include "../lib/stringh.h"
#include "soundlib.h"

class Sound
{
	public:
		Sound(music_t*);
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
		static Sound* getSound(std::string);
		static std::list<Sound*>::iterator getSoundIterator(std::string);
		virtual ~Sound();
	private:
		std::string name;
		sf::SoundBuffer sndbf;
		sf::Sound* snd;	
		static std::list<Sound*> sounds;
};


#endif // __SOUND_H_
