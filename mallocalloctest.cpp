#define _CRT_SECURE_NO_WARNINGS 1

#include "MallocAlloc.h"


typedef _MallocAllocTemplate<0> Malloc_Alloc;


void DoFreeAlloc()
{
	for (int i = 0;; ++i)
	{
		cout << "tyring to release space" << endl;
	}
}

void test1()
{

	int* p = (int*)Malloc_Alloc::Allocate(sizeof(int)* 5);
	for (size_t i = 0; i < 5; ++i)
	{
		p[i] = i;
	}

	p = (int*)Malloc_Alloc::Reallocate(p, sizeof(int)* 10);
	for (int i = 5; i < 10; ++i)
	{
		p[i] = i;
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << p[i] << " ";
	}
	cout << endl;
	Malloc_Alloc::Deallocate(p);
}

void test2()
{

	Malloc_Alloc::Set_Malloc_Handler(DoFreeAlloc);
	int* p = (int*)Malloc_Alloc::Allocate(sizeof(int*)* (102410241024));
	Malloc_Alloc::Deallocate(p);
}

int main()
{
	test1();
	test2();
	system("pause");
	return 0;
}