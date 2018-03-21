#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
using namespace std;
#include <assert.h>


//������ȡ
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
	//�޲ι��캯��
	Vector()
		:_start(0)
		, _finish(0)
		, _endOfStorage(0)
	{}
	//�вι��캯��
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
	//�������캯��
	Vector(const Vector& v)
		:_start(new T[v.Size()])
		, _finish(_start + v.Size())
		, _endOfStorage(_finish)
	{
		_Copy(_start, v._start, v.Size());
	}
	//��ֵ���������
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
	//��������
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
	//β��
	void PushBack(const T& data)
	{
		_CheckCapacity();
		*_finish++ = data;
	}
	//βɾ
	void PopBack()
	{
			--_finish;
	}
	//����λ�ò���
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
	//����λ��ɾ��
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
	//��ȡ��ЧԪ�ظ���
	size_t Size()const
	{
		return _finish - _start;
	}
	//��ȡ����
	size_t Capacity()const
	{
		return _endOfStorage - _start;
	}
	//�ж��Ƿ�Ϊ��
	bool Empty()const
	{
		return _start == _finish;
	}
	//����ЧԪ�ظ�����ΪnewSize��
	void Resize(size_t newSize, const T& data = T())
	{
		if (newSize <= Size())//newSizeС����ЧԪ�ظ���
		{
			_finish = _start + newSize;
		}
		else if (newSize > Size() && newSize <= Capacity())//newSize������ЧԪ�ظ�����С������
		{
			for (size_t i = Size(); i < newSize; i++)
			{
				_start[i] = data;
			}
			_finish = _start + newSize;
		}
		else//newSize��������
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
	//�����±������
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
	//������Ԫ��
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
	//����βԪ��
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
	//���˳���
	void Clear()
	{
		_finish = _start;
	}
private:
	//�������
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
	//������������
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