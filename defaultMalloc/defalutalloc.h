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

	//将申请的字节数上调至8的整数倍
	static size_t Round_Up(size_t n)
	{
		return (n + _ALIGN - 1) & (~(_ALIGN - 1));
	}

	//寻找合适的下标
	static  size_t Free_List_Index(size_t n) 
	{
		return (n + _ALIGN - 1) / _ALIGN - 1;
	}

	static void* Allocate(size_t n)
	{
		if (n > _MAX_BYTES)
		{
			//printf("n大于128字节，调用一级空间配置器")；
			__TRACE_DEBUG(" %d大于128字节，调用一级空间配置器申请空间\n", n);
			return _MallocAllocTemplate<inst>::Allocate(n);
		}
		__TRACE_DEBUG(" %d小于128字节，调用二级空间配置器申请空间\n", n);
		size_t index = Free_List_Index(n);
		if (freelist[index] == NULL)
		{
			__TRACE_DEBUG(" 链表%d(%d)桶中没有可用的内存块，调用refill填充链表\n", index, n);
			return ReFill(Round_Up(n));
		}
		else
		{
			__TRACE_DEBUG(" 链表中有可用空闲块\n");
			OBJ* result = freelist[index];
			freelist[index] = result->freeListLink;
			return result;
		}
	}

	static void Deallocate(void* p, size_t n)
	{
		if (n > _MAX_BYTES)
		{
			__TRACE_DEBUG(" %d大于128字节，调用一级空间配置器释放\n", n);
			return _MallocAllocTemplate<inst>::Deallocate(p);
		}
		
		size_t index = Free_List_Index(n);

		((OBJ*)p)->freeListLink = freelist[index];
		freelist[index] = (OBJ*)p;
		__TRACE_DEBUG(" 归还了%d字节的内存块到链表里\n", n);
	}

	//填充内存池
	static void* ReFill(size_t n)
	{
		int nobjs = 20;
		char* chunk = Chunk_Alloc(n, nobjs);

		if (nobjs == 1)
			return chunk;

		size_t index = Free_List_Index(n);
		OBJ* cur = (OBJ*)(chunk + n);

		__TRACE_DEBUG(" 内存池补充了%d个%d字节的小块内存\n", nobjs, n);

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

	//内存池函数
	static char* Chunk_Alloc(size_t n, int& nobjs)
	{
		size_t totalBytes = nobjs*n;
		size_t leftBytes = _endfree - _startfree;

		if (totalBytes <= leftBytes)//内存池空间足够
		{
			__TRACE_DEBUG(" 内存池空间足够，分配20个%d字节的内存块\n",n);
			char* res = _startfree;
			_startfree += totalBytes;
			return res;
		}
		else if (leftBytes >= n)//不够20个，但至少可以申请一个
		{
			nobjs = leftBytes / n;
			__TRACE_DEBUG(" 内存池空间不够，只能能申请%d个%d字节的内存块\n", nobjs, n);
			totalBytes = n*nobjs;
			char* res = _startfree;
			_startfree += totalBytes;
			return res;
		}
		else//一个都不能申请
		{
			__TRACE_DEBUG(" 内存池连一个%d字节的内存块都不能申请了\n",n);
			if (leftBytes > 0)
			{
				__TRACE_DEBUG(" 将内存池剩下的%d字节的内存块挂在链表上\n", leftBytes);
				size_t index = Free_List_Index(leftBytes);
				((OBJ*)_startfree)->freeListLink = freelist[index];
				freelist[index] = (OBJ*)_startfree;
			}
			size_t GetBytes = totalBytes * 2 + (Round_Up(_heapsize >> 4));
			_startfree = (char*)malloc(GetBytes);

			__TRACE_DEBUG(" 向系统申请内存%d字节的空间\n", GetBytes);

			if (_startfree == NULL)//向堆空间申请内存失败
			{
				__TRACE_DEBUG(" 向堆空间申请内存失败，看链表中还有没有更大的空间\n");
				//看链表中还有没有更大的空闲空间
				size_t index = Free_List_Index(n);
				for (; index < _NFREELISTS; index++)
				{
					OBJ* p = freelist[index];
					if (p != NULL)
					{
						__TRACE_DEBUG(" 链表%d中还有大的空间\n",index);
						freelist[index] = p->freeListLink;
						_startfree = (char*)p;
						_endfree = _startfree + (index + 1)*_ALIGN;

						return Chunk_Alloc(n, nobjs);
					}
				}
				_endfree = 0;
				__TRACE_DEBUG(" 山穷水尽了，求助一级空间配置器\n");
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