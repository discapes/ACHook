#pragma once
#include <cstdint>
#include <Windows.h>
#include "def.h"
#include "ld32.h"

#define isRet(oc) oc == 0xC3 || oc == 0xCB || oc == 0xC2 || oc == 0xCA

class hook {
public:

	const size_t len;
	const byte* oBytes;
	const byte* nBytes;

	hook(const byte* oFun, const byte* hkFun)
	:
		len ( calcLength(oFun) ),
		oBytes ( copyBytes(oFun, len) ),
		nBytes ( createJump(oFun, hkFun) ),
		gateway ( createGateway(oFun, len) ) 
	{}
	
	~hook() {
		delete[] oBytes;
		delete[] nBytes;
		VirtualFree(gateway, 0, MEM_RELEASE);
	}

	void doHook() {
		memcpy(oFun, nBytes, len);
	}

	void unHook() {
		memcpy(oFun, oBytes, len);
	}

private:

	byte* oFun;
	byte* gateway;
	
	byte* createJump(const byte* from, const byte* to) {
		byte* buffer = new byte[len];
		buffer[0] = 0xE9;
		*(uintptr_t*)(buffer + 1) = to - (from + 5);
	}

	size_t calcLength(const byte* oFun) {
		size_t len = 0;
		while ((len += length_disasm(oFun)) < 5);
		upto(len - 1, i)
			if (isRet(*(oFun + i)))
				throw "Can't hook, would overwrite after return";
		return len;
	}

	byte* copyBytes(const byte* source, size_t len) {
		byte* buffer = new byte[len];
		memcpy(buffer, source, len);
	}

	byte* createGateway(const byte* oFun, size_t len) {
		byte* gateway = (byte*)VirtualAlloc(NULL, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (gateway == 0) throw "Could not allocate memory for gateway";
		memcpy(gateway, oFun, len);
		byte* jump = createJump(gateway, oFun);
		return gateway;
	}
};