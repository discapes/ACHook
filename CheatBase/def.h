#pragma once
#include <cstdint>
#include <iostream>
#include <initializer_list>
#include "Array.h"
#define loop(v,m) for(int v = 0; v<int(m); v++)
#define loopi(m) loop(i,m)
#define loopj(m) loop(j,m)
#define loopk(m) loop(k,m)
#define loopl(m) loop(l,m)
using std::cout;
using std::endl;

typedef unsigned int uint;
typedef uint8_t byte;
typedef uint32_t dword;
typedef unsigned char uchar;

inline void printAdr(std::string name, void* value) {
	cout << name << ": 0x" << value << endl;
}

#define printVar(name, value) cout << name << ": " << value << endl;
#define isRet(oc) oc == 0xC3 || oc == 0xCB || oc == 0xC2 || oc == 0xCA