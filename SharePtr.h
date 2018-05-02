#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
using namespace std;


//声明WeakPtr
template <class T>
class WeakPtr;


//引用计数，更实用更复杂
template<class T>
class SharePtr
{
	//将WeakPtr定义为SharePtr的友元
	friend class WeakPtr<T>;
public:

	SharePtr(T* ptr)
		:_ptr(ptr)
		, _count(new int(1))
	{}

	SharePtr(SharePtr<T>& sp)
		:_ptr(sp._ptr)
		,_count(sp._count)
	{
		(*_count)++;
	}

	SharePtr<T>& operator=(const SharePtr<T>& sp)
	{
		if (*this != sp)
		{
			if (_prt && --(*_count) == 0)
			{
				delete _ptr;
				delete _count;
			}
			_ptr = sp._ptr;
			_count = sp._count;
			(*_count)++;
		}
		return *this;
	}

	~SharePtr()
	{
		if (--(*_count) == 0)
		{
			delete _ptr;
			delete _count;
			_ptr = NULL;
			_count = NULL;
		}
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
	int* _count;
};
