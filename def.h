#pragma once
#include <cstdint>
#define loop(v,m) for(int v = 0; v<int(m); v++)
#define loopi(m) loop(i,m)
#define loopj(m) loop(j,m)
#define loopk(m) loop(k,m)
#define loopl(m) loop(l,m)
#define once(f) { static bool first = true; if (first) { f first = false; } }
#define ifPressed(k) if (GetAsyncKeyState(k) & 1)
#define prt(x) std::cout << x << '\n'

typedef unsigned int uint;
typedef uint8_t byte;
typedef uint32_t dword;
typedef unsigned char uchar;