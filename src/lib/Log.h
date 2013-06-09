#ifndef __LOG_H_
#define __LOG_H_

#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/SplitterChannel.h>
#include <falcon/engine.h>
#include "stringh.h"

namespace PE
{
	namespace Logging
	{
		enum Levels
		{
			ERROR,
			WARNING,
			NOTICE,
			INFORMATION
		};
	};
};

class Log
{
	public:
		static void log(PE::Logging::Levels, std::string);
		static void log(std::string);
	private:
		static Poco::AutoPtr<Poco::FileChannel> fChan;
		static Poco::AutoPtr<Poco::ConsoleChannel> conChan;
		static Poco::AutoPtr<Poco::SplitterChannel> sChan;
		static void setup();
		static bool stp;
};

FALCON_FUNC FWrapLog(Falcon::VMachine* vm);
		

#endif // __LOG_H_
