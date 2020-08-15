#pragma once
#include <cstdint>
using namespace std;

class Offsets {
	const uintptr_t* const offsets;
public:
	const size_t size;
	const uintptr_t operator[](size_t i) { return offsets[i]; }
	Offsets(initializer_list<uintptr_t> offsets) : offsets(offsets.begin()), size(offsets.size()) {}
};