#ifndef __LOADFALCON_H_
#define __LOADFALCON_H_

#include <string>
#include "FalconM.h"
int loadFalcon(std::string loadScript, bool core, std::string modulenm, int params, bool option=false, FalconM* fsm=0);

#endif // __LOADFALCON_H_
