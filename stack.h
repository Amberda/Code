#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include "vector.h"
//ģ�����
template<class T,class Container>
class Stack1
{
public:
	Stack1()//���캯��
	{}
	void Push(const T data)
	{
		_con.PushBack(data);
	}
	void Pop()
	{
		_con.PopBack();
	}
	bool Empty()
	{
		return _con.Empty();
	}
	size_t Size()
	{
		return _con.Size();
	}
	T& Top()
	{
		return _con.Back();
	}
	const T& Top()const
	{
		return _con.Back();
	}
private:
	Container _con;
};

//ģ���ģ�����
template<class T, template<class > class Container >
class Stack2
{
public:
	Stack2()//���캯��
	{}
	void Push(const T data)
	{
		_con.PushBack(data);
	}
	void Pop()
	{
		_con.PopBack();
	}
	bool Empty()
	{
		return _con.Empty();
	}
	size_t Size()
	{
		return _con.Size();
	}
	T& Top()
	{
		return _con.Back();
	}
	const T& Top()const
	{
		return _con.Back();
	}
private:
	Container<T> _con;
};