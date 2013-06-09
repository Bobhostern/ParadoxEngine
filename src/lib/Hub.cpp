#include "Hub.h"
#include "stringh.h"

std::map<std::string, HubVariable> Hub::variables;

void Hub::registerDouble(std::string ky, double vr)
{
	HubVariable hbvr;
	hbvr.vartype = PE::Hub::DOUBLE;
	hbvr.doubl = vr;

	variables[ky] = hbvr;	
}

void Hub::registerInteger(std::string ky, int vr)
{
	HubVariable hbvr;
	hbvr.vartype = PE::Hub::INTEGER;
	hbvr.integer = vr;

	variables[ky] = hbvr;	
}

void Hub::registerString(std::string ky, std::string vr)
{
	HubVariable hbvr;
	hbvr.vartype = PE::Hub::STRING;
	hbvr.string = new std::string(vr);

	variables[ky] = hbvr;	
}

void Hub::registerBoolean(std::string ky, bool vr)
{
	HubVariable hbvr;
	hbvr.vartype = PE::Hub::BOOLEAN;
	hbvr.boolean = vr;

	variables[ky] = hbvr;	
}

HubVariable Hub::grabVariable(std::string key)
{
	if(variables.find(key) != variables.end())
	{
		return variables.find(key)->second;
	}
	else
	{
		HubVariable rtnl;
		rtnl.vartype = PE::Hub::VOID;
		return rtnl;
	}
}

FALCON_FUNC varDouble(Falcon::VMachine* vm)
{
	Falcon::Item* ky = vm->param(0);
	Falcon::Item* vl = vm->param(1);

	if((ky == NULL || !ky->isString())
		|| (vl == NULL || !vl->isNumeric()))
	{
		throw new Falcon::ParamError(Falcon::ErrorParam(Falcon::e_inv_params, __LINE__)
		.extra("String, Numeric"));
	}
	
	Hub::registerDouble(FString::fromStringS(*ky->asString()), vl->asNumeric());
}

FALCON_FUNC varInteger(Falcon::VMachine* vm)
{
	Falcon::Item* ky = vm->param(0);
	Falcon::Item* vl = vm->param(1);

	if((ky == NULL || !ky->isString())
		|| (vl == NULL || !vl->isInteger()))
	{
		throw new Falcon::ParamError(Falcon::ErrorParam(Falcon::e_inv_params, __LINE__)
		.extra("String, Integer"));
	}
	
	Hub::registerInteger(FString::fromStringS(*ky->asString()), vl->forceInteger());
}

FALCON_FUNC varString(Falcon::VMachine* vm)
{
	Falcon::Item* ky = vm->param(0);
	Falcon::Item* vl = vm->param(1);

	if((ky == NULL || !ky->isString())
		|| (vl == NULL || !vl->isString()))
	{
		throw new Falcon::ParamError(Falcon::ErrorParam(Falcon::e_inv_params, __LINE__)
		.extra("String, String"));
	}
	
	Hub::registerString(FString::fromStringS(*ky->asString()), FString::fromStringS(*vl->asString()));
}

FALCON_FUNC varBoolean(Falcon::VMachine* vm)
{
	Falcon::Item* ky = vm->param(0);
	Falcon::Item* vl = vm->param(1);

	if((ky == NULL || !ky->isString())
		|| (vl == NULL || !vl->isBoolean()))
	{
		throw new Falcon::ParamError(Falcon::ErrorParam(Falcon::e_inv_params, __LINE__)
		.extra("String, Boolean"));
	}
	
	Hub::registerBoolean(FString::fromStringS(*ky->asString()), vl->asBoolean());
}

FALCON_FUNC varGet(Falcon::VMachine* vm)
{
	Falcon::Item* ky = vm->param(0);

	if(ky == NULL || !ky->isString())
	{
		throw new Falcon::ParamError(Falcon::ErrorParam(Falcon::e_inv_params, __LINE__)
		.extra("String"));
	}
	
	HubVariable var = Hub::grabVariable(FString::fromStringS(*ky->asString()));
	
	switch(var.vartype)
	{
		case PE::Hub::DOUBLE:
			vm->retval(var.doubl);
			break;
		case PE::Hub::INTEGER:
			vm->retval(Falcon::int64(var.integer));
			break;
		case PE::Hub::STRING:
			vm->retval(FString::fromString(*var.string));
			break;
		case PE::Hub::BOOLEAN:
			vm->retval(var.boolean);
			break;
		case PE::Hub::VOID:
			vm->retnil();
	}
}
