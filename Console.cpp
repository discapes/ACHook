#include <windows.h>
#include <conio.h>
#include <FCNTL.H>
#include <io.h>
#include "Console.h"
#include <iostream>

namespace Console
{
	static FILE* in;
	static FILE* err;
	static FILE* out;
	static bool allocated = false;

	static BOOL WINAPI MyConsoleCtrlHandler(DWORD dwCtrlEvent) { return dwCtrlEvent == CTRL_C_EVENT; }

	void open()
	{
		if (!AllocConsole()) return;
		freopen_s(&in, "CONIN$", "r", stdin);
		freopen_s(&err, "CONOUT$", "w", stderr);
		freopen_s(&out, "CONOUT$", "w", stdout);
		SetConsoleCtrlHandler(MyConsoleCtrlHandler, TRUE);
		RemoveMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
		allocated = true;
	}

	void close()
	{
		if (!allocated) return;
		fclose(in);
		fclose(err);
		fclose(out);
		SetConsoleCtrlHandler(MyConsoleCtrlHandler, FALSE);
		FreeConsole();
	}
}