#pragma once
#include "MallocAlloc.h"


template<bool threads,int inst>
class DefalutAllocTemplate
{
private:

	enum { _ALIGN = 8 };
	enum { _MAX_BYTES = 128 };
	enum { _NFREELISTS = 16 }; // _MAX_BYTES/_ALIGN

	union OBJ
	{
		OBJ* freeListLink;
		char clientData[1];
	};

	static OBJ* freelist[_NFREELISTS];

	static char* _startfree;
	static char* _endfree;
	static size_t _heapsize;

public:

	//��������ֽ����ϵ���8��������
	static size_t Round_Up(size_t n)
	{
		return (n + _ALIGN - 1) & (~(_ALIGN - 1));
	}

	//Ѱ�Һ��ʵ��±�
	static  size_t Free_List_Index(size_t n) 
	{
		return (n + _ALIGN - 1) / _ALIGN - 1;
	}

	static void* Allocate(size_t n)
	{
		if (n > _MAX_BYTES)
		{
			//printf("n����128�ֽڣ�����һ���ռ�������")��
			__TRACE_DEBUG(" %d����128�ֽڣ�����һ���ռ�����������ռ�\n", n);
			return _MallocAllocTemplate<inst>::Allocate(n);
		}
		__TRACE_DEBUG(" %dС��128�ֽڣ����ö����ռ�����������ռ�\n", n);
		size_t index = Free_List_Index(n);
		if (freelist[index] == NULL)
		{
			__TRACE_DEBUG(" ����%d(%d)Ͱ��û�п��õ��ڴ�飬����refill�������\n", index, n);
			return ReFill(Round_Up(n));
		}
		else
		{
			__TRACE_DEBUG(" �������п��ÿ��п�\n");
			OBJ* result = freelist[index];
			freelist[index] = result->freeListLink;
			return result;
		}
	}

	static void Deallocate(void* p, size_t n)
	{
		if (n > _MAX_BYTES)
		{
			__TRACE_DEBUG(" %d����128�ֽڣ�����һ���ռ��������ͷ�\n", n);
			return _MallocAllocTemplate<inst>::Deallocate(p);
		}
		
		size_t index = Free_List_Index(n);

		((OBJ*)p)->freeListLink = freelist[index];
		freelist[index] = (OBJ*)p;
		__TRACE_DEBUG(" �黹��%d�ֽڵ��ڴ�鵽������\n", n);
	}

	//����ڴ��
	static void* ReFill(size_t n)
	{
		int nobjs = 20;
		char* chunk = Chunk_Alloc(n, nobjs);

		if (nobjs == 1)
			return chunk;

		size_t index = Free_List_Index(n);
		OBJ* cur = (OBJ*)(chunk + n);

		__TRACE_DEBUG(" �ڴ�ز�����%d��%d�ֽڵ�С���ڴ�\n", nobjs, n);

		while (--nobjs)
		{
			cur->freeListLink = freelist[index];
			freelist[index] = cur;
			OBJ* next = (OBJ*)((char*)cur + n);
			cur = next;
		  /*cur = (OBJ*)((char*)cur + n);*/
		}
		return chunk;
	}

	//�ڴ�غ���
	static char* Chunk_Alloc(size_t n, int& nobjs)
	{
		size_t totalBytes = nobjs*n;
		size_t leftBytes = _endfree - _startfree;

		if (totalBytes <= leftBytes)//�ڴ�ؿռ��㹻
		{
			__TRACE_DEBUG(" �ڴ�ؿռ��㹻������20��%d�ֽڵ��ڴ��\n",n);
			char* res = _startfree;
			_startfree += totalBytes;
			return res;
		}
		else if (leftBytes >= n)//����20���������ٿ�������һ��
		{
			nobjs = leftBytes / n;
			__TRACE_DEBUG(" �ڴ�ؿռ䲻����ֻ��������%d��%d�ֽڵ��ڴ��\n", nobjs, n);
			totalBytes = n*nobjs;
			char* res = _startfree;
			_startfree += totalBytes;
			return res;
		}
		else//һ������������
		{
			__TRACE_DEBUG(" �ڴ����һ��%d�ֽڵ��ڴ�鶼����������\n",n);
			if (leftBytes > 0)
			{
				__TRACE_DEBUG(" ���ڴ��ʣ�µ�%d�ֽڵ��ڴ�����������\n", leftBytes);
				size_t index = Free_List_Index(leftBytes);
				((OBJ*)_startfree)->freeListLink = freelist[index];
				freelist[index] = (OBJ*)_startfree;
			}
			size_t GetBytes = totalBytes * 2 + (Round_Up(_heapsize >> 4));
			_startfree = (char*)malloc(GetBytes);

			__TRACE_DEBUG(" ��ϵͳ�����ڴ�%d�ֽڵĿռ�\n", GetBytes);

			if (_startfree == NULL)//��ѿռ������ڴ�ʧ��
			{
				__TRACE_DEBUG(" ��ѿռ������ڴ�ʧ�ܣ��������л���û�и���Ŀռ�\n");
				//�������л���û�и���Ŀ��пռ�
				size_t index = Free_List_Index(n);
				for (; index < _NFREELISTS; index++)
				{
					OBJ* p = freelist[index];
					if (p != NULL)
					{
						__TRACE_DEBUG(" ����%d�л��д�Ŀռ�\n",index);
						freelist[index] = p->freeListLink;
						_startfree = (char*)p;
						_endfree = _startfree + (index + 1)*_ALIGN;

						return Chunk_Alloc(n, nobjs);
					}
				}
				_endfree = 0;
				__TRACE_DEBUG(" ɽ��ˮ���ˣ�����һ���ռ�������\n");
				_startfree = (char*)_MallocAllocTemplate<inst>::Allocate(n);
			}

			_heapsize += GetBytes;
			_endfree = _startfree + GetBytes;
			return Chunk_Alloc(n, nobjs);
		}
	}
};

template <bool threads,int inst>
char *DefalutAllocTemplate<threads, inst>::_startfree = 0;

template <bool threads, int inst>
char *DefalutAllocTemplate<threads, inst>::_endfree = 0;

template <bool threads, int inst>
size_t DefalutAllocTemplate<threads, inst>::_heapsize= 0; 

template <bool threads,int inst>
typename DefalutAllocTemplate<threads, inst>::OBJ*
DefalutAllocTemplate<threads, inst>::freelist[_NFREELISTS] = { 0 };


#ifdef USE_MALLOC
typedef _MallocAllocTemplate<0> _Alloc;
#else
typedef DefalutAllocTemplate<false, 0> _Alloc;
#endif

template <class T, class Alloc = _Alloc>
class SimpleAlloc
{
public:
	static T *Allocate(size_t n)
	{
		return n == 0 ? 0 : (T*)Alloc::Allocate(sizeof(T)*n);
	}
	static T* Allocate(void)
	{
		return (T*)Alloc::Allocate(sizeof(T));
	}

	static void Deallocate(T* p, size_t n)
	{
		if (n != 0)
		{
			Alloc::Deallocate(p, sizeof(T)*n);
		}
	}
	static void Deallocate(T* p)
	{
		Alloc::Deallocate(p, sizeof(T*));
	}
};