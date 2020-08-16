#include <iostream>
#include <Windows.h>
#include "SDK.h"
#include "mem.h"
#include "Console.h"
#include "def.h"
#include <io.h>
#include <fcntl.h>
#include "Patch.h"

static BOOL WINAPI MyConsoleCtrlHandler(DWORD dwCtrlEvent) { return dwCtrlEvent == CTRL_C_EVENT; }

DWORD WINAPI mainThread(HMODULE hModule)
{
	Console::open();
	byte* ac_client = (byte*)GetModuleHandle(L"ac_client.exe");
	printAdr("ac_client", ac_client);
	playerent* localPlayer = *(playerent**)(ac_client + 0x10F4F4);
	printAdr("localPlayer", localPlayer);

	Patch infAmmo(ac_client + 0x637E9, Array<byte>(0x90, 2));

	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
			*localPlayer->weaponsel->mag = 1337;

		if (GetAsyncKeyState(VK_DELETE) & 1)
			localPlayer->health = 1337;

		if (GetAsyncKeyState(VK_HOME) & 1)
			infAmmo.toggle();

		if (GetAsyncKeyState(VK_END) & 1)
			break;
	}

	Console::close();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)mainThread, hModule, 0, nullptr);
		if (handle) CloseHandle(handle);
		break;
	}
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	case DLL_PROCESS_DETACH: break;
	}
	return TRUE;
}