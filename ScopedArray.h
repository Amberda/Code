#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>


template<class T>
class ScopedArray
{
public:
	ScopedArray(const T* ptr)
		:_ptr(ptr)
	{}
	~ScopedArray()
	{
		if (_ptr)
		{
			delete[] _ptr;
		}
	}
	T& operator[](size_t index)
	{
		return _ptr[index];
	}
private:
	ScopedArray(const ScopedArray<T>& sa);
	ScopedArray<T>& operator=(const ScopedArray<T>& sa);
private:
	T* _ptr;
};