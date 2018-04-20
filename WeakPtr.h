#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>
#include "SharePtr.h"

template <class T>
class WeakPtr
{
public:
	WeakPtr()
		:_ptr(NULL)
	{}

	WeakPtr(const SharePtr<T>& sp)
		:_ptr(sp._ptr)
	{}

	WeakPtr<T>* operator=(const SharePtr<T>& sp)
	{
		_ptr = sp._ptr;
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

private:
	T* _ptr;
};