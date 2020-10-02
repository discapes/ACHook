#include <iostream>
#include <Windows.h>
#include "Console.h"
#include "def.h"
#include "Patch.h"
#include "Hook.h"
#include "AC/SDK.h"

static Hook<int(__stdcall*)(HDC)>* pwglSwapBuffers;
static HMODULE hModule;

int __stdcall hk_wglSwapBuffers(HDC hDC)
{
	static auto& wglSwapBuffers = *pwglSwapBuffers;
	static byte* ac_client = (byte*)GetModuleHandle(L"ac_client.exe");
	static playerent* localPlayer = *(playerent**)(ac_client + 0x10F4F4);

	once(
		Console::open();
		prt("ac_client : " << (void*)ac_client);
		prt("localPlayer : " << (void*)localPlayer);
	)

	ifPressed(VK_INSERT)
		*localPlayer->weaponsel->mag = 1337;

	ifPressed(VK_DELETE)
		localPlayer->health = 1337;

	ifPressed(VK_HOME)
	{
		static Patch infAmmo(ac_client + 0x637E9, SmartArray<byte>( 0x90, 2 ));
		infAmmo.toggle();
	}

	int ret = wglSwapBuffers(hDC);

	ifPressed(VK_END)
	{
		Console::close();
		delete pwglSwapBuffers;
		FreeLibrary(hModule);
	}

	return ret;
}

DWORD WINAPI mainThread(HMODULE _hModule)
{
	pwglSwapBuffers = new Hook(L"opengl32.dll", "wglSwapBuffers", hk_wglSwapBuffers);
	hModule = _hModule;
	pwglSwapBuffers->toggle();
	return 0;
}

BOOL APIENTRY DllMain(HMODULE _hModule, DWORD  ul_reason_for_call, LPVOID)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)mainThread, _hModule, 0, nullptr);
		if (handle) CloseHandle(handle);
		break;
	}
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	case DLL_PROCESS_DETACH: break;
	}
	return TRUE;
}