#pragma once

#include <iostream>
#include <stdlib.h>
using namespace std;
#include <Windows.h>
#include <string.h>

#define _THROW_BAN_ALLOC 0


static string GetFileName(const string& path)
{
	char ch = '/';
#ifdef _WIN32       
	ch = '\\';
#endif
	size_t pos = path.rfind(ch);
	if (pos == string::npos)
		return path;
	else
		return path.substr(pos + 1);
}

// 用于调试追踪的trace log 
inline static void _trace_debug(const char * funcName, const char * fileName, int line, char* format, ...)
{
	fprintf(stdout, "[%s:%d]%s", GetFileName(fileName).c_str(), line, funcName);
	// 输出用户信息        
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
}
#define __TRACE_DEBUG(...) \
	_trace_debug(__FUNCDNAME__, __FILE__, __LINE__, __VA_ARGS__);



//一级空间配置器
template<int inst>
class _MallocAllocTemplate
{
public:
	static void* Allocate(size_t n)//开辟空间
	{
		void* result = malloc(n);//调用malloc开辟空间
		if (result == 0)
		{
			result = _Oom_Malloc(n);//开辟失败就调用_Oom_Malloc
		}
		__TRACE_DEBUG(" 一级空间配置器申请成功：%d\n", n);
		return result;
	}

	static void* Reallocate(void* p, size_t n)//开辟空间，在源空间的基础上
	{
		void* result = realloc(p, n);//调用realloc开辟空间
		if (result == 0)
		{
			result = _Oom_Realloc(p, n);//开辟失败调用_Oom_Realloc
		}
		return result;
	}

	static void Deallocate(void* p)//释放空间
	{
		__TRACE_DEBUG(" 一级空间配置器来释放\n");
		free(p);//内部调用free释放空间
	}

	//该函数接收一个返回值为空，参数为空的函数指针作为参数，最后返回一个返回值和参数均为空的函数指针
	static void(*Set_Malloc_Handler(void(*f)()))()
	{
		void(*old)() = _Malloc_Alloc_Oom_Handler;//保存旧的处理例程
		_Malloc_Alloc_Oom_Handler = f;			//重新设置新的处理例程
		return old;
	}

private:

	static void(*_Malloc_Alloc_Oom_Handler)();

	static void* _Oom_Malloc(size_t n)
	{
		void(*_My_Malloc_Handler)();
		void* result;

		__TRACE_DEBUG(" 一级空间配置器第一次申请失败，_Oom_Malloc来处理\n");

		for (;;)
		{
			_My_Malloc_Handler = _Malloc_Alloc_Oom_Handler;//用户自定义处理函数
			//因为内存不足处理函数初值设置的是0，如果用户没有自定义，就直接抛出异常
			if (_My_Malloc_Handler == 0)
			{
				_THROW_BAN_ALLOC;
			}
			(*_My_Malloc_Handler)();//若定义了，则调用用户自定义处理函数
			result = malloc(n);//再次开辟内存
			if (result)
				return result;
		}
		//不断的尝试释放和配置是因为用户不知道还需要释放多少内存来满足分配需求，只能逐步的释放配置
	}

	static void* _Oom_Realloc(void* p, size_t n)
	{
		void(*_My_Malloc_Handler)();
		void* result;

		for (;;)
		{
			_My_Malloc_Handler = _Malloc_Alloc_Oom_Handler;
			if (_My_Malloc_Handler == 0)
			{
				_THROW_BAN_ALLOC;
			}
			(*_My_Malloc_Handler)();
			result = realloc(p, n);
			if (result)
				return result;
		}
	}
};

//内存不足处理函数初值设置为0，等用户自己定义  
template<int inst>
void(*_MallocAllocTemplate<inst>::_Malloc_Alloc_Oom_Handler)() = 0;

