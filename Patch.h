#pragma once
#include <cstdint>
#include <Windows.h>
#include "LDE/ld32.h"
#include "SmartArray.h"

class Patch
{
	byte* oFun;
	bool enabled;
public:
	const size_t patchSize;
	const SmartArray<byte> oBytes;
	const SmartArray<byte> nBytes;

	Patch(byte* oFun, SmartArray<byte>&& nBytes)
		:
		enabled(false),
		patchSize(nBytes.size),
		oBytes(std::move(SmartArray<byte>(oFun, patchSize))),
		nBytes(std::move(nBytes)),
		oFun(oFun)
	{}

	void doPatch()
	{
		enabled = true;
		DWORD oldProtect;
		VirtualProtect(oFun, patchSize, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(oFun, nBytes.data, patchSize);
		VirtualProtect(oFun, patchSize, oldProtect, &oldProtect);
	}

	void unPatch()
	{
		enabled = false;
		DWORD oldProtect;
		VirtualProtect(oFun, patchSize, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(oFun, oBytes.data, patchSize);
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