#pragma once
#include "def.h"

namespace mem
{

	uintptr_t resolvePointer(uintptr_t addr, arr<uint> offsets);

}