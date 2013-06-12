#include "Game.h"

using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;

bool Game::onInit()
{
	if(!findConfigs())
	{
		return false;
	}
	loadFalcon(Info::getGameFolderName() + "onLoad.fal", true, "__main__", 0);
	return true;
}

bool Game::findConfigs()
{
	AutoPtr<PropertyFileConfiguration> pConf;
	try
	{
		pConf = new PropertyFileConfiguration("PEconf/conf.prop");
		if(pConf->getString("game.type") == "FOLDER")
			Info::setGameName(pConf->getString("game.name"));
		else if(pConf->getString("game.type") == "CDIR")
			Info::setGameName("");
	}
	catch(Poco::FileNotFoundException ex)
	{
		Log::log(PE::Logging::WARNING, "Cannot find PEconf/conf.prop");
		return false;
	}
	catch(Poco::NotFoundException ex)
	{
		Log::log(PE::Logging::WARNING, "conf.prop needs game.name and/or game.type defined");
		return false;
	}
	return true;
}

int Game::run()
{
	return onCleanup();
}

int Game::onCleanup()
{
	loadFalcon(Info::getGameFolderName() + "onClose.fal", true, "__main__", 0, true);
	return 0;
}

