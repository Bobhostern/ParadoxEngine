#ifndef __GAME_H_
#define __GAME_H_

#include <Poco/Foundation.h>
#include <Poco/Util/PropertyFileConfiguration.h>
#include "loadFalcon.h"
#include "Log.h"
#include "Info.h"

class Game
{
	public:
		bool onInit();
		int run();
	private:
		bool findConfigs();
		int onCleanup();
};

#endif // __GAME_H_
