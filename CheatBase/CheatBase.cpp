#include <iostream>
#include <Windows.h>
#include "PrintValue.h"
#include "Process.h"
using namespace std;

const wchar_t* procName = L"ac_client.exe";

int main() {
	try {
		Process game = Process(procName);

		DWORD procId = game.getProcId();
		printHex("procId", procId);

		uintptr_t moduleBase = game.getModuleBaseAddress(procName);
		printHex("moduleBase", moduleBase);

		uintptr_t pLocalPlayer = moduleBase + 0x10F4F4;
		printHex("pLocalPlayer", pLocalPlayer);

		uintptr_t pAmmo = game.resolvePointer(pLocalPlayer, { 0x374, 0x14, 0x0 });
		printHex("pAmmo", pAmmo);

		int ammo = game.read<int>(pAmmo);
		printDec("*pAmmo", ammo);

		cout << "Changing ammo..." << endl;
		game.write<int>(pAmmo, 1337);

		ammo = game.read<int>(pAmmo);
		printDec("*pAmmo", ammo);
	}
	catch (wstring err) { wcout << err; };
}