#include <Windows.h>
#include <TlHelp32.h>
#include "Offsets.h"
using namespace std;

class Process {
	HANDLE hProc;
	DWORD procId;
	const wstring procName;

public:
	HANDLE getHProc() {
		return hProc;
	}
	
	DWORD getProcId() {
		return procId;
	}

	const wstring getProcName() {
		return procName;
	}

	Process(const wstring procName) : procName(procName), procId(-1) {
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 procEntry;
			procEntry.dwSize = sizeof(procEntry);

			if (Process32First(hSnap, &procEntry))
			{
				do
				{
					if (!_wcsicmp(procEntry.szExeFile, procName.c_str()))
					{
						procId = procEntry.th32ProcessID;
						break;
					}
				} while (Process32Next(hSnap, &procEntry));
			}
		}
		if (procId == -1) {
			wstring procStr(procName);
			throw L"Could not find process "s + procStr;
		}
		CloseHandle(hSnap);
		hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	}


	uintptr_t getModuleBaseAddress(const wstring modName) {
		uintptr_t modBaseAddr = -1;
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
		if (hSnap != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 modEntry;
			modEntry.dwSize = sizeof(modEntry);
			if (Module32First(hSnap, &modEntry))
			{
				do
				{
					if (!_wcsicmp(modEntry.szModule, modName.c_str()))
					{
						modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
						break;
					}
				} while (Module32Next(hSnap, &modEntry));
			}
		}
		if (modBaseAddr == -1) throw L"Could not find module "s + modName;
		CloseHandle(hSnap);
		return modBaseAddr;
	}

	uintptr_t resolvePointer(uintptr_t addr, Offsets offsets) {
		for (size_t i = 0; i < offsets.size; ++i)
		{
			ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
			addr += offsets[i];
		}
		return addr;
	}

	template<class T>
	T read(uintptr_t address) {
		T value;
		ReadProcessMemory(hProc, (BYTE*)address, &value, sizeof(T), nullptr);
		return value;
	}

	template<class T>
	void write(uintptr_t address, T value) {
		WriteProcessMemory(hProc, (BYTE*)address, &value, sizeof(T), nullptr);
	}
};