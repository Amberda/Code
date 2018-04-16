#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
using namespace std;


//���������򵥴ֱ�
template<class T>
class ScopedPtr
{
public:
	ScopedPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}
	~ScopedPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
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
	//ֻ������ʵ�֣�������Ϊ˽��
	ScopedPtr(const ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(const ScopedPtr<T>& sp);
private:
	T* _ptr;
};
