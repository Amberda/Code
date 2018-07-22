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

// ���ڵ���׷�ٵ�trace log 
inline static void _trace_debug(const char * funcName, const char * fileName, int line, char* format, ...)
{
	fprintf(stdout, "[%s:%d]%s", GetFileName(fileName).c_str(), line, funcName);
	// ����û���Ϣ        
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
}
#define __TRACE_DEBUG(...) \
	_trace_debug(__FUNCDNAME__, __FILE__, __LINE__, __VA_ARGS__);



//һ���ռ�������
template<int inst>
class _MallocAllocTemplate
{
public:
	static void* Allocate(size_t n)//���ٿռ�
	{
		void* result = malloc(n);//����malloc���ٿռ�
		if (result == 0)
		{
			result = _Oom_Malloc(n);//����ʧ�ܾ͵���_Oom_Malloc
		}
		__TRACE_DEBUG(" һ���ռ�����������ɹ���%d\n", n);
		return result;
	}

	static void* Reallocate(void* p, size_t n)//���ٿռ䣬��Դ�ռ�Ļ�����
	{
		void* result = realloc(p, n);//����realloc���ٿռ�
		if (result == 0)
		{
			result = _Oom_Realloc(p, n);//����ʧ�ܵ���_Oom_Realloc
		}
		return result;
	}

	static void Deallocate(void* p)//�ͷſռ�
	{
		__TRACE_DEBUG(" һ���ռ����������ͷ�\n");
		free(p);//�ڲ�����free�ͷſռ�
	}

	//�ú�������һ������ֵΪ�գ�����Ϊ�յĺ���ָ����Ϊ��������󷵻�һ������ֵ�Ͳ�����Ϊ�յĺ���ָ��
	static void(*Set_Malloc_Handler(void(*f)()))()
	{
		void(*old)() = _Malloc_Alloc_Oom_Handler;//����ɵĴ�������
		_Malloc_Alloc_Oom_Handler = f;			//���������µĴ�������
		return old;
	}

private:

	static void(*_Malloc_Alloc_Oom_Handler)();

	static void* _Oom_Malloc(size_t n)
	{
		void(*_My_Malloc_Handler)();
		void* result;

		__TRACE_DEBUG(" һ���ռ���������һ������ʧ�ܣ�_Oom_Malloc������\n");

		for (;;)
		{
			_My_Malloc_Handler = _Malloc_Alloc_Oom_Handler;//�û��Զ��崦����
			//��Ϊ�ڴ治�㴦������ֵ���õ���0������û�û���Զ��壬��ֱ���׳��쳣
			if (_My_Malloc_Handler == 0)
			{
				_THROW_BAN_ALLOC;
			}
			(*_My_Malloc_Handler)();//�������ˣ�������û��Զ��崦����
			result = malloc(n);//�ٴο����ڴ�
			if (result)
				return result;
		}
		//���ϵĳ����ͷź���������Ϊ�û���֪������Ҫ�ͷŶ����ڴ��������������ֻ���𲽵��ͷ�����
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

//�ڴ治�㴦������ֵ����Ϊ0�����û��Լ�����  
template<int inst>
void(*_MallocAllocTemplate<inst>::_Malloc_Alloc_Oom_Handler)() = 0;

