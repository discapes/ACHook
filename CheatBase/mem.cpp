#include "mem.h"
#include "def.h"

uintptr_t mem::resolvePointer(uintptr_t addr, Array<uint> offsets) {
	for (size_t i = 0; i < offsets.size; ++i)
	{
		addr = *(uintptr_t*)addr;
		addr += (offsets[i]);
	}
	return addr;
}