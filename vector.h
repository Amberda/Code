#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
using namespace std;
#include <assert.h>


//类型萃取
//-----------------------------------------------
struct TrueType
{
	bool Get()
	{
		return true;
	}
};
struct FalseType
{
	bool Get()
	{
		return false;
	}
};
template<class T>
struct TypeTraits
{
	typedef FalseType IsPOD;
};
template<>
struct TypeTraits<int>
{
	typedef TrueType IsPOD;
};
template<>
struct TypeTraits<char>
{
	typedef TrueType IsPOD;
};
template<>
struct TypeTraits<double>
{
	typedef TrueType IsPOD;
};
template<>
struct TypeTraits<float>
{
	typedef TrueType IsPOD;
};
template<>
struct TypeTraits<long>
{
	typedef TrueType IsPOD;
};
template<class T>
void _Copy(T* dst,T* const& src,size_t size)
{
	if (TypeTraits<T>::IsPOD().Get())
	{
		memcpy(dst, src, size*sizeof(T));
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			dst[i] = src[i];
		}
	}
}
//-----------------------------------------------

template<class T>
class Vector
{
public:
	typedef T* Iterator;
	typedef const T* IteratorConst;
public:
	//无参构造函数
	Vector()
		:_start(0)
		, _finish(0)
		, _endOfStorage(0)
	{}
	//有参构造函数
	Vector(const T* array,size_t size)
		:_start(new T[size])
		, _finish(_start)
		, _endOfStorage(_start+size)
	{
		for (size_t i = 0; i < size; i++)
		{
			*_finish++ = array[i];
		}
	}
	//拷贝构造函数
	Vector(const Vector& v)
		:_start(new T[v.Size()])
		, _finish(_start + v.Size())
		, _endOfStorage(_finish)
	{
		_Copy(_start, v._start, v.Size());
	}
	//赋值运算符重载
	Vector& operator =(const Vector& v)
	{
		if (this != &v)
		{
			T* tmp = new T[v.Size()];
			_Copy(tmp, v._start, v.Size());
			delete[] _start;
			_start = tmp;
			_finish = _start + v.Size();
			_endOfStorage = _finish;
		}
		return *this;
	}
	//析构函数
	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = 0;
			_finish = 0;
			_endOfStorage = 0;
		}
	}

	////////////////////iterator////////////////////
	Iterator Begin()
	{
		return _start;
	}
	IteratorConst Begin()const
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}
	IteratorConst End()const
	{
		return _finish;
	}
	////////////////////Modify////////////////////
	//尾插
	void PushBack(const T& data)
	{
		_CheckCapacity();
		*_finish++ = data;
	}
	//尾删
	void PopBack()
	{
			--_finish;
	}
	//任意位置插入
	void Insert(size_t pos, const T& data)
	{
		assert(pos <= Size());
		_CheckCapacity();
		for (size_t i = Size(); i > pos; i--)
		{
			_start[i] = _start[i - 1];
		}
		_start[pos] = data;
		++_finish;
	}
	//任意位置删除
	void Erase(size_t pos)
	{
		assert(pos < Size());
		for (size_t i = pos; i < Size() - 1; i++)
		{
			_start[i] = _start[i + 1];
		}
		--_finish;
	}

	////////////////////capacity//////////////////// 
	//获取有效元素个数
	size_t Size()const
	{
		return _finish - _start;
	}
	//获取容量
	size_t Capacity()const
	{
		return _endOfStorage - _start;
	}
	//判断是否为空
	bool Empty()const
	{
		return _start == _finish;
	}
	//将有效元素个数改为newSize个
	void Resize(size_t newSize, const T& data = T())
	{
		if (newSize <= Size())//newSize小于有效元素个数
		{
			_finish = _start + newSize;
		}
		else if (newSize > Size() && newSize <= Capacity())//newSize大于有效元素个数但小于容量
		{
			for (size_t i = Size(); i < newSize; i++)
			{
				_start[i] = data;
			}
			_finish = _start + newSize;
		}
		else//newSize大于容量
		{
			T* temp = new T[newSize];
			for (size_t i = 0; i < Size(); i++)
			{
				temp[i] = _start[i];
			}
			for (size_t i = Size(); i < newSize; i++)
			{
				temp[i] = data;
			}
			delete[] _start;
			_start = temp;
			_finish = _start + newSize;
			_endOfStorage = _finish;
		}
	}

	////////////////////Acess//////////////////// 
	//重载下标运算符
	T& operator[](size_t index)
	{
		assert(_start);
		return _start[index];
	}
	const T& operator[](size_t index)const
	{
		assert(_start);
		return _start[index];
	}
	//返回首元素
	T& Front()
	{
		assert(_start);
		return _start[0];
	}
	const T& Front()const
	{
		assert(_start);
		return _start[0];
	}
	//返回尾元素
	T& Back()
	{
		assert(_start);
		return _start[Size() - 1];
	}
	const T& Back()const
	{
		assert(_start);
		//return _start[Size() - 1];
		return *(End() - 1);
	}
	//清空顺序表
	void Clear()
	{
		_finish = _start;
	}
private:
	//检查容量
	void _CheckCapacity()
	{
		T* temp;
		if (_finish == _endOfStorage)
		{
			size_t capacity = 2 * (_endOfStorage - _start) + 3;
			temp = new T[capacity];
			T* pos = _start;
			size_t i = 0;
			while (pos < _endOfStorage)
			{
				temp[i++] = *pos++;
			}
			delete _start;
			_start = temp;
			_finish = _start + i;
			_endOfStorage = _start + capacity;
		}
	}
	//重载输出运算符
	template<class T>
	friend ostream& operator<<(ostream& _cout, const Vector<T>& d)
	{
		for (size_t i = 0; i < d.Size(); i++)
		{
			_cout << d[i] << " ";
		}
		return _cout;
	}

private:
	T* _start;
	T* _finish;
	T* _endOfStorage;

};