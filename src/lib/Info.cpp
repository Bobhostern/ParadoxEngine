#include "Info.h"
#include "Log.h"
#include "stringh.h"
#include <iostream>
#include "../api/API.h"

std::string Info::_name = "";
bool Info::gns = false;

double Info::getVersionNum()
{
	return 0.02;
}

std::string Info::getGameName()
{
	return _name;
}

std::string Info::getGameFolderName()
{
	if(_name != "")
		return _name + "/";
	else
		return _name;
}

void Info::setGameName(std::string nme)
{
	if(!gns)
	{
		_name = nme;
		gns = true;
	}
}

FALCON_FUNC VNumFWrap(Falcon::VMachine* vm)
{
	vm->retval(Falcon::numeric(Info::getVersionNum()));
}

FALCON_FUNC GNmeFWrap(Falcon::VMachine* vm)
{
	vm->retval(FString::fromString(Info::getGameName()));
}

FALCON_FUNC FEngineCheck(Falcon::VMachine* vm)
{
	Falcon::Item* gvrs = vm->param(0);
	
	if(gvrs == NULL || !gvrs->isOrdinal())
	{
		throw new Falcon::ParamError(Falcon::ErrorParam(Falcon::e_inv_params, __LINE__)
		.extra("Integer"));
	}
	
	if(!(Info::getVersionNum() == gvrs->asNumeric()))
	{
		if(!(Info::getVersionNum() > gvrs->asNumeric()))
		{
			std::string gameNum = String<double>::toString(gvrs->asNumeric());
			std::string engineNum = String<double>::toString(Info::getVersionNum());
			Log::log("Version mismatch\nGame: " + gameNum + "\nEngine: " + engineNum);
		}
		else
		{
			std::string gameNum = String<double>::toString(gvrs->asNumeric());
			std::string engineNum = String<double>::toString(Info::getVersionNum());
			Log::log(PE::Logging::WARNING, "The game may work, may have some bugs, a lot of bugs, or the game won't work at all.\nThat's because you are using an Engine version " + engineNum + " with a Game version " + gameNum + ".\nDo you wish to continue? Answer Yes to agree.");
			std::string ans;
			std::cin >> ans;
			std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
			Log::log(PE::Logging::NOTICE, "User answered " + ans + ". (" + ((ans != "yes") ? "rejected" : "accepted") + ")");
			if(ans != "yes")
			{
				exit(-1);
			}
		}
	}
	vm->retval(true);
}  
