#define _CRT_SECURE_NO_WARNINGS 1

#include <stdlib.h>
#include <stdarg.h>
#include "defalutalloc.h"


void Testdefalutalloc()
{
	int *p = SimpleAlloc<int, _Alloc>::Allocate(200);

	SimpleAlloc<int, _Alloc>::Deallocate(p, 200);

	int *p1 = SimpleAlloc<int, _Alloc>::Allocate(2);
	SimpleAlloc<int, _Alloc>::Deallocate(p1, 2);

	p1 = SimpleAlloc<int, _Alloc>::Allocate(5);

	int* p2 = SimpleAlloc<int, _Alloc>::Allocate(3);

	SimpleAlloc<int, _Alloc>::Deallocate(p1, 5);
	SimpleAlloc<int, _Alloc>::Deallocate(p2, 3);

}

int main()
{
	Testdefalutalloc();
	system("pause");
	return 0;
}