#ifndef __HUB_H_
#define __HUB_H_

#include <falcon/engine.h>
#include <map>
#include "stringh.h"

namespace PE
{
	namespace Hub
	{
		enum VarTypes
		{
			DOUBLE,
			INTEGER,
			STRING,
			BOOLEAN,
			VOID
		};
	};
};

struct HubVariable
{
	PE::Hub::VarTypes vartype;
	union
	{	
		double doubl;
		int integer;
		std::string* string;
		bool boolean;
	};
};


class Hub
{
	public:
		static void registerDouble(std::string,double);
		static void registerInteger(std::string,int);
		static void registerString(std::string,std::string);
		static void registerBoolean(std::string,bool);
		static HubVariable grabVariable(std::string);
	private:
		static std::map<std::string, HubVariable> variables;
};

FALCON_FUNC varDouble(Falcon::VMachine* vm);
FALCON_FUNC varInteger(Falcon::VMachine* vm);
FALCON_FUNC varString(Falcon::VMachine* vm);
FALCON_FUNC varBoolean(Falcon::VMachine* vm);
FALCON_FUNC varGet(Falcon::VMachine* vm);

#endif // __HUB_H_
