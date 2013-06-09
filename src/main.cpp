#include <Poco/Foundation.h>
#include <Poco/Util/PropertyFileConfiguration.h>
#include "lib/loadFalcon.h"
#include "lib/Log.h"
#include "lib/Info.h"

using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;

int main()
{
   	AutoPtr<PropertyFileConfiguration> pConf;
	try
	{
		pConf = new PropertyFileConfiguration("PEconf/conf.prop");
		Info::setGameName(pConf->getString("game.name"));
	}
	catch(Poco::FileNotFoundException ex)
	{
		Log::log("Cannot find PEconf/conf.prop");
	}
	catch(Poco::NotFoundException ex)
	{
		Log::log("conf.prop needs game.name defined");
	}
        loadFalcon(Info::getGameFolderName() + "game.fal", true, "onLoad", 0);
        loadFalcon(Info::getGameFolderName() + "game.fal", true, "onClose", 0, true);
}
