#pragma once
#include <cstdint>
#include <iostream>
#include <initializer_list>
#define loop(v,m) for(int v = 0; v<int(m); v++)
#define loopi(m) loop(i,m)
#define loopj(m) loop(j,m)
#define loopk(m) loop(k,m)
#define loopl(m) loop(l,m)
using namespace std;

template <typename T>
class arr {
	T* data;
public:
	const size_t size;
	T operator[] (int index) {
		return data[index];
	}
	arr(std::initializer_list<T> list)
		: size(list.size())
	{
		data = new T[size];
		memcpy(data, list.begin(), size);
	}
	~arr() {
		delete[] data;
	}
};

typedef unsigned int uint;
typedef uint8_t byte;
typedef uint32_t dword;
typedef arr<byte> bytes;
typedef unsigned char uchar;

template<typename T>
inline void printAdr(std::string name, T value) {
	cout << name << ": 0x" << std::hex << std::uppercase << (uintptr_t)value << endl;
}

template<typename T>
inline void printDec(std::string name, T value) {
	cout << name << ": " << std::dec << (uintptr_t)value << endl;
}