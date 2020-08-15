#pragma once
#include <cstdint>
#include <initializer_list>
#define upto(len, i) for (int i = 0; i < (len); i++)

template <typename T>
struct arr {
	const T* arr;
	const size_t size;
	T& operator[] (int index) {
		return arr[index];
	}
	arr(std::initializer_list<T> list)
		: size(list.size)
	{
		arr = new T[size];
		memcpy(arr, init.begin(), size);
	}
};

typedef unsigned int uint;
typedef uint8_t byte;
typedef uint32_t dword;
typedef arr<uint> bytes;