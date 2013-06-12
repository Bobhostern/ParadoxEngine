#include "FalconM.h"
#include "Log.h"
#include "Info.h"
#include "stringh.h"
#include "../sound/MusicFileLoader.h"
#include "Hub.h"
#ifndef _NO_WAIT_FUNC
	#include <SDL/SDL.h>
#endif

FalconM::FalconM()
{
	Falcon::Engine::Init();
}

FalconM::~FalconM()
{
	Falcon::Engine::Shutdown();
}

int FalconM::embed(std::string script_name, bool core, std::string funcname, int params)
{
	Falcon::ModuleLoader theLoader(".");
	theLoader.addFalconPath();
	theLoader.addDirectoryBack(FString::fromString("./" + Info::getGameFolderName()));	

	Falcon::Runtime rt(&theLoader);
	rt.loadFile(script_name.c_str());
	
	Falcon::VMachineWrapper vm;
	
	if (core)
		vm->link(Falcon::core_module_init());
	Falcon::Module* mod = createAppModule();
	vm->link(mod);
	
	vm->link(&rt);
	vm->launch(funcname.c_str(), params);
	return 0;
}

FALCON_FUNC createCard(Falcon::VMachine* vm)
{
	if(vm->param(0) == 0 || !(vm->param(0)->isString()))
	{
		throw new Falcon::ParamError(
			Falcon::ErrorParam(Falcon::e_inv_params, __LINE__).
			extra("String") );
	}
	Falcon::Item* name = vm->param(0);
	
	Falcon::CoreObject* self = vm->self().asObject();
	self->setProperty("name", *name);
}

Falcon::Module* FalconM::createAppModule()
{
	Falcon::Module* module = new Falcon::Module;
	module->name("ParadoxEngine");
	
	/* Examples
	module->addConstant("YGOMX_NULL", Falcon::int64(YGOMX::YGOMX_NIL));
	
	//module->addExtFunc("sleep", SysScriptSleep);
	
	module->addClassMethod(cls_pinfo, "fromTileset", &FTileFromXML).
		asSymbol()->addParam("tileset")->addParam("idcode");*/

	#ifndef _NO_WAIT_FUNC
	module->addExtFunc("wait", waitSeconds);
	#endif

	Falcon::Symbol* single_appinfo = module->addSingleton("Info");
	Falcon::Symbol* cls_pinfo = single_appinfo->getInstance();
	module->addClassMethod(cls_pinfo, "engineVersion", &VNumFWrap);
	module->addClassMethod(cls_pinfo, "gameName", &GNmeFWrap);

	module->addConstant("LOG_LEVEL_NOTICE", Falcon::int64(PE::Logging::NOTICE));
	module->addConstant("LOG_LEVEL_INFORMATION", Falcon::int64(PE::Logging::INFORMATION));
	module->addConstant("LOG_LEVEL_WARNING", Falcon::int64(PE::Logging::WARNING));
	module->addConstant("LOG_LEVEL_ERROR", Falcon::int64(PE::Logging::ERROR));
	Falcon::Symbol* single_appinfo2 = module->addSingleton("Logger");
	Falcon::Symbol* cls_pinfo2 = single_appinfo2->getInstance();
	module->addClassMethod(cls_pinfo2, "log", &FWrapLog);
	
	Falcon::Symbol* single_appinfo3 = module->addSingleton("Game");
	Falcon::Symbol* cls_pinfo3 = single_appinfo3->getInstance();
	module->addClassMethod(cls_pinfo3, "versionCheck", &FEngineCheck);

	Falcon::Symbol* single_appinfo6 = module->addSingleton("MusicEngine");
	Falcon::Symbol* cls_pinfo6 = single_appinfo6->getInstance();
	module->addClassMethod(cls_pinfo6, "loadMusic", &loadMusic);

	module->addConstant("HUBVAR_DOUBLE", Falcon::int64(PE::Hub::DOUBLE));
	module->addConstant("HUBVAR_INTEGER", Falcon::int64(PE::Hub::INTEGER));
	module->addConstant("HUBVAR_STRING", Falcon::int64(PE::Hub::STRING));
	module->addConstant("HUBVAR_BOOLEAN", Falcon::int64(PE::Hub::BOOLEAN));
	Falcon::Symbol* single_appinfo7 = module->addSingleton("Hub");
	Falcon::Symbol* cls_pinfo7 = single_appinfo7->getInstance();
	module->addClassMethod(cls_pinfo7, "setDouble", &varDouble);
	module->addClassMethod(cls_pinfo7, "setInteger", &varInteger);
	module->addClassMethod(cls_pinfo7, "setString", &varString);
	module->addClassMethod(cls_pinfo7, "setBoolean", &varBoolean);
	module->addClassMethod(cls_pinfo7, "getVariable", &varGet);
	module->addClassMethod(cls_pinfo7, "deleteVariable", &varDel);
	module->addClassMethod(cls_pinfo7, "setVariable", &varSet);
	
	return module;
}

/*
static FALCON_FUNC pushCard(Falcon::VMachine* vm)
{
	Falcon::Item* it = vm->param(0);
	vm->retval();
}
*/

#ifndef _NO_WAIT_FUNC

void breakTime(int seconds)
{
	SDL_Delay(seconds * 1000);
}

FALCON_FUNC waitSeconds(Falcon::VMachine* vm)
{
	Falcon::Item* secs = vm->param(0);
	if(secs == NULL || !secs->isOrdinal())
	{
		throw new Falcon::ParamError(Falcon::ErrorParam(Falcon::e_inv_params, __LINE__)
		.extra("Ordinal"));
	}
	
	if(vm->systemData().sleep(secs->asNumeric()))
		breakTime(secs->asNumeric());
}

#endif
