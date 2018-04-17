#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
using namespace std;


//����Ȩת�ƣ�����ȱ�ݵ����
template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{}
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}
	AutoPtr<T>& operator=(const AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			//���ͷ�ԭ�ռ�
			if (_ptr)
				delete _ptr;
			//��ֵ
			_ptr = ap._ptr;
			//����Ȩת��
			ap._ptr = NULL;
		}
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
	~AutoPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}
private:
	T* _ptr;
};