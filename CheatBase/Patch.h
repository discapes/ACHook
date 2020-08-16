#pragma once
#include <cstdint>
#include <Windows.h>
#include "def.h"
#include "ld32.h"

class Patch
{
	byte* oFun;
	bool enabled;
public:
	const size_t patchSize;
	const Array<byte> oBytes;
	const Array<byte> nBytes;

	Patch(byte* oFun, const Array<byte> newBytes)
		:
		enabled(false),
		patchSize(newBytes.size),
		oBytes(Array<byte>(oFun, patchSize)),
		nBytes(newBytes),
		oFun(oFun)
	{}

	~Patch()
	{
		cout << "~Patch()\n";
	}

	void doPatch()
	{
		enabled = true;
		DWORD oldProtect;
		VirtualProtect(oFun, patchSize, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(oFun, nBytes, patchSize);
		VirtualProtect(oFun, patchSize, oldProtect, &oldProtect);
	}

	void unPatch()
	{
		enabled = false;
		DWORD oldProtect;
		VirtualProtect(oFun, patchSize, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(oFun, oBytes, patchSize);
		VirtualProtect(oFun, patchSize, oldProtect, &oldProtect);
	}

	void toggle()
	{
		enabled = !enabled;
		if (enabled) doPatch();
		else unPatch();
	}

	bool isEnabled() { return enabled; }
};