#ifndef __MUSICFILELOADER_H_
#define __MUSICFILELOADER_H_

#include <falcon/engine.h>
#include "../xsd/music.h"

class MusicFileLoader
{
	public:
		static void loadMusic(musicfile_t*);
};
	
FALCON_FUNC loadMusic(Falcon::VMachine* vm);

#endif // __MUSICFILELOADER_H_
