#pragma once
#include <cstdint>
#include <Windows.h>
#include "def.h"
#include "Patch.h"
#include "ld32.h"

class Hook : public Patch 
{
	byte* oFun;
	byte* gateway;
public:

	Hook(byte* oFun, const byte* hkFun)
		:
		Patch(oFun, createJump(oFun, hkFun)),
		gateway ( createGateway(oFun, patchSize) ) 
	{}
	
	~Hook() {
		cout << "~Hook()\n";
		VirtualFree(gateway, 0, MEM_RELEASE);
	}

private:
	
	void placeJump(const byte* from, const byte* to, byte* jump) {
		jump[0] = 0xE9;
		*(uintptr_t*)(jump + 1) = to - (from + 5);
	}

	Array<byte>& createJump(const byte* from, const byte* to)
	{
		Array<byte> jump(5);
		jump[0] = 0xE9;
		*(uintptr_t*)(jump + 1) = to - (from + 5);
		return jump;
	}

	size_t calcLength(const byte* oFun) {
		size_t len = 0;
		while ((len += length_disasm(oFun)) < 5);
		loopi(len - 1)
			if (isRet(*(oFun + i)))
				throw "Can't hook, would overwrite after return";
		return len;
	}

	byte* createGateway(const byte* oFun, size_t len) {
		byte* gateway = (byte*)VirtualAlloc(NULL, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (gateway == 0) throw "Could not allocate memory for gateway";
		memcpy(gateway, oFun, len);
		placeJump(gateway, oFun, gateway + len);
		return gateway;
	}
};