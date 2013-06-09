#include "MusicFileLoader.h"
#include "../lib/Log.h"
#include "../lib/Info.h"
#include "../lib/stringh.h"
#include "Music.h"
#include "Sound.h"

void MusicFileLoader::loadMusic(musicfile_t* mscldxml)
{
	musicfile_t::music_sequence& seq(mscldxml->music());
	for(musicfile_t::music_iterator x = seq.begin(); x != seq.end(); x++)
	{
		music_t& msc(*x);
		if(msc.musictype() == "MUSIC")
		{
			Music(new music_t(*x));
		}
		else if(msc.musictype() == "SOUND")
		{
			Sound(new music_t(*x));
		}
		else
		{
			Log::log("Invalid music type specified: " + msc.musictype());
		}
	}
}

FALCON_FUNC loadMusic(Falcon::VMachine* vm)
{
	try
	{
		MusicFileLoader::loadMusic(&*musicfile(Info::getGameFolderName() + "music/musicload.mscld"));
		vm->retval(true);
	}
	catch(const xml_schema::exception& ex)
	{
		Log::log(String<const xml_schema::exception&>::toString(ex));
	}
}
