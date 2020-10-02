#pragma once
#include <cstdint>
#include <Windows.h>
#include "def.h"
#include "Patch.h"
#include "LDE/ld32.h"

#define isRet(oc) oc == 0xC3 || oc == 0xCB || oc == 0xC2 || oc == 0xCA

template <typename T>
class Hook : public Patch 
{
	byte* oFun;
	T gateway;
	int _counter = 0;

public:

	int& counter()
	{
		return _counter;
	}

	Hook(byte* oFun, const byte* hkFun)
		:
		Patch(oFun, std::move(createJump(oFun, hkFun))),
		gateway ( (T)createGateway(oFun, patchSize) ) 
	{}
	
	Hook(T oFun, const T hkFun)
		: 
		Hook((byte*)oFun, (const byte*)hkFun)
	{}

	Hook(const wchar_t* modName, const char* procName, const T hkFun)
		: Hook((byte*)GetProcAddress(GetModuleHandle(modName), procName), (byte*)hkFun)
	{}

	~Hook() {
		unPatch();
		VirtualFree(gateway, 0, MEM_RELEASE);
	}

	template <typename... P>
	std::invoke_result_t<T, P...> operator()(P&&... args)
	{
		_counter++;
		return gateway(std::forward<P>(args)...);
	}

private:
	
	void placeJump(byte* jump, const byte* to) {
		jump[0] = 0xE9;
		*(uintptr_t*)(jump + 1) = to - (jump + 5);
	}

	SmartArray<byte> createJump(const byte* from, const byte* to)
	{
		SmartArray<byte> jump(5);
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
		placeJump(gateway + len, oFun + len);
		return gateway;
	}
};