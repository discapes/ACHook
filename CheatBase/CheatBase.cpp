#include <iostream>
#include <Windows.h>
#include "SDK.h"
#include "mem.h"
#include "def.h"

const wchar_t* modName = L"ac_client.exe";

DWORD WINAPI mainThread(HANDLE hModule) {
	while (true) {
		byte* ac_client = (byte*)GetModuleHandle(modName);
		printAdr("ac_client", ac_client);

		playerent* localPlayer = *(playerent**)(ac_client + 0x10F4F4);
		printAdr("localPlayer", localPlayer);

		int* ammo = localPlayer->weaponsel->ammo;
		printDec("ammo", ammo);

		cout << "Changing ammo..." << endl;
		*ammo = 1337;
		printDec("ammo", ammo);
	}
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE handle = CreateThread(nullptr, 0, mainThread, hModule, 0, nullptr);
		if (handle) CloseHandle(handle);
		break;
	}
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	case DLL_PROCESS_DETACH: break;
	}
	return TRUE;
}