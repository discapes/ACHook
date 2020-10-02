#pragma once

template <typename T>
struct SmartArray
{
	T* data = nullptr;
	size_t size = 0;

	SmartArray() = default;

	void swap(SmartArray<T>&& with)
	{
		std::swap(data, with.data);
		std::swap(size, with.size);
	}

	explicit SmartArray(size_t size)
		:
		size(size),
		data(size ? new T[size]{} : nullptr)
	{}

	SmartArray(T val, size_t size)
		: SmartArray(size)
	{
		std::fill_n(data, size, val);
	}

	SmartArray(const T* data, size_t size)
		: SmartArray(size)
	{
		std::copy_n(data, size, this->data);
	}

	SmartArray(std::initializer_list<T> list)
		: SmartArray(list.begin(), list.size())
	{}

	SmartArray(const SmartArray<T>& orig)
		: SmartArray(orig.data, orig.size)
	{}

	SmartArray(SmartArray<T>&& orig) noexcept
	{
		swap(std::move(orig));
	}

	SmartArray& operator=(const SmartArray<T>& orig)
	{
		swap(SmartArray(orig.data, orig.size));
		return *this;
	}

	SmartArray& operator=(SmartArray<T>&& orig) noexcept
	{
		swap(std::move(orig));
		return *this;
	}

	~SmartArray()
	{
		delete[] data;
	}

	T& operator[] (int index) const
	{
		return data[index];
	}

	operator T* ()
	{
		return data;
	}

	void print()
	{
		std::cout << " [";
		for (size_t i = 0; i < size; i++)
			std::cout << " " << data[i];
		std::cout << " ]\n";
	}
};