#ifndef __INFO_H_
#define __INFO_H_

#include "stringh.h"
#include <falcon/engine.h>

class Info
{
	public:
		static double getVersionNum();
		static std::string getGameName();
		static std::string getGameFolderName();
		static void setGameName(std::string);
	private:
		static std::string _name;
		static bool gns;
};

FALCON_FUNC VNumFWrap(Falcon::VMachine* vm);
FALCON_FUNC GNmeFWrap(Falcon::VMachine* vm);
FALCON_FUNC FEngineCheck(Falcon::VMachine* vm);

#endif // __INFO_H_
