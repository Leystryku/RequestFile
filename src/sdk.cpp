#include "sdk.h"

IVEngineClient *g_pEngine = 0;
ICvar* g_pCVar = 0;

std::string InitializeSdk()
{
	HMODULE g_EngineDLL = GetModuleHandle("engine.dll");

	if ( !g_EngineDLL  )
	{
		Sleep(200);
		return InitializeSdk();
	}

	CreateInterfaceFn g_EngineFactory = (CreateInterfaceFn)GetProcAddress(g_EngineDLL, "CreateInterface");
	const char *has_Failed = NULL;

	if ( !g_EngineFactory  )
	{
		has_Failed = "Could not get a factory";
		MessageBox(NULL, has_Failed, "grr", MB_OK);

		return 0;
	}

	//Get Interfaces
	g_pEngine = (IVEngineClient*)g_EngineFactory("VEngineClient012", 0);//cssv34 = VEngineClient012, else 13


	if (!g_pEngine)
	{
		return "g_pEngine == NULL";
	}



	return "";

}
