#include "FalconM.h"
#include <iostream>
#include <cstdlib>

int loadFalcon(std::string loadScript, bool core, std::string modulenm, int params, bool option=false, FalconM* fsm=0)
{
	if(fsm == 0)
		fsm = new FalconM;
	try
	{
		return fsm->embed(loadScript, core, modulenm, params);
	}
	catch (Falcon::Error* err)
	{
		Falcon::AutoCString edesc(err->toString());
		std::cerr << edesc.c_str() << std::endl;
		err->decref();
		if(option)
			return -1;
		exit(-1);
	}
}
