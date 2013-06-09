#ifndef __FALCONM_H_
#define __FALCONM_H_

#include <falcon/engine.h>
#include "stringh.h"

class FalconM
{
	public:
		FalconM();
		virtual ~FalconM();
		int embed(std::string script_name, bool core, std::string funcname, int params);
	private:
		Falcon::Module* createAppModule();
};

/* static FALCON_FUNC pushCard(Falcon::VMachine* vm); */

#endif // __FALCONM_H_
