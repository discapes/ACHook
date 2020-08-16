#pragma once
#include <iostream>
#include "def.h"
using std::cout;
using std::endl;

template <typename T>
class Array
{
	T* arr;
public:

	const size_t size;

	Array(std::initializer_list<T> list)
		: Array(list.begin(), list.size())
	{}
	Array(const T* oData, size_t size)
		: size(size)
	{
		arr = new T[size];
		memcpy(arr, oData, sizeof(T) * size);
	}
	Array(size_t size)
		: size(size)
	{
		arr = new T[size];
	}
	Array(const T val, size_t size)
		: size(size)
	{
		arr = new T[size];
		memset(arr, val, sizeof(T) * size);
	}

	~Array()
	{
		cout << "~Array()\n";
		delete[] arr;
	}

	Array(const Array<T>& orig)
	: 
		Array(orig, orig.size)
	{
		cout << "Copy constructor\n";
	}

	T& operator[] (int index) const
	{
		return arr[index];
	}
	operator T*() const
	{
		return arr;
	}
};