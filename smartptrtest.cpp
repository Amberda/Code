#define _CRT_SECURE_NO_WARNINGS 1
#include "ScopedPtr.h"

#include <memory>
//#include <boost/scoped_ptr.hpp>

//¶¨ÖÆÉ¾³ýÆ÷-----·Âº¯Êý
class Delete1
{
public:
	void operator()(FILE* f)
	{
		fclose(f);
	}
};
class Delete2
{
public:
	void operator()(void* p)
	{
		free(p);
	}
};


void smartptrTest()
{
	auto_ptr<int> ap1(new int(10));
	auto_ptr<int> ap2(ap1);

//	boost::scoped_ptr<int> sp1(new int(20));
//  boost::scoped_ptr<int> sp2(sp1);
}

void FunTest2()
{
	ScopedPtr<int> sp1(new int);
}
int main()
{
	FunTest2();
	system("pause");
	return 0;
}