#include "Log.h"
#include <cstdlib>
#include <Poco/Logger.h>

using namespace Poco;

AutoPtr<FileChannel> Log::fChan = new FileChannel;
AutoPtr<ConsoleChannel> Log::conChan = new ConsoleChannel;
AutoPtr<SplitterChannel> Log::sChan = new SplitterChannel;
bool Log::stp = false;

void Log::setup()
{
	if(!stp)
	{
		fChan->setProperty("path", "./log.txt");
		fChan->setProperty("compress", "true");
		fChan->setProperty("archive", "number");
		fChan->setProperty("purgeCount", "50");
		fChan->setProperty("rotation", "2 K");

		sChan->addChannel(fChan);
		sChan->addChannel(conChan);
	
		Logger::root().setLevel("trace");
		Logger::root().setChannel(fChan);
		Logger::root().information("---Loaded logging...---");
		Logger::root().setChannel(sChan);
		stp = true;
	}
}

void Log::log(PE::Logging::Levels lv, std::string str)
{
	setup();
	switch(lv)
	{
		case PE::Logging::INFORMATION:
			str = "INFORMATION: " + str;
			Logger::root().information(str.c_str());
			break;
		case PE::Logging::NOTICE:
			str = "NOTICE: " + str;
			Logger::root().information(str.c_str());
			break;
		case PE::Logging::WARNING:
			str = "WARNING: " + str;
			Logger::root().warning(str.c_str());
			break;
		case PE::Logging::ERROR:
			str = "ERROR: " + str;
			Logger::root().error(str.c_str());
			exit(-1);
	}
}

void Log::log(std::string str)
{
	setup();
	str = "ERROR: " + str;
	Logger::root().error(str.c_str());
	exit(-1);
}

FALCON_FUNC FWrapLog(Falcon::VMachine* vm)
{
	Falcon::Item* lglv = vm->param(0);
	Falcon::Item* message = vm->param(1);
	
	if((lglv == NULL || !lglv->isInteger())
		|| (message == NULL || !message->isString()))
	{
		throw new Falcon::ParamError(Falcon::ErrorParam(Falcon::e_inv_params, __LINE__)
		.extra("LOG_LEVEL, String"));
	}
	
	PE::Logging::Levels lvl = PE::Logging::Levels(lglv->forceInteger());
	std::string mess = FString::fromStringS(*message->asString());

	Log::log(lvl, mess);
}
