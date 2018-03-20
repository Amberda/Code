#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <string.h>
#include <Windows.h>


class String
{
public:
	String(const char* pStr = "")
	{
		if (pStr == NULL)
		{
			_pStr = new char[1];
			*_pStr = '\0';
		}
		else
		{
			_pStr = new char[strlen(pStr) + 1];
			strcpy(_pStr, pStr);
		}
	}
	//浅拷贝
	//String(const String& s)
	//	:_pStr(s._pStr)
	//{}
	//String& operator=(const String& s)
	//{
	//	if (this != &s)
	//	{
	//		_pStr = s._pStr;
	//	}
	//	return *this;
	//}

	//深拷贝普通版
	String(const String& s)
		:_pStr(new char[strlen(s._pStr) + 1])
	{
		strcpy(_pStr, s._pStr);
	}
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* temp = new char[strlen(s._pStr) + 1];
			strcpy(temp, s._pStr);
			delete[] _pStr;
			_pStr = temp;
		}
		return *this;
	}
	//深拷贝简洁版
	//String(const String& s)
	//{
	//	String strTemp(s._pStr);
	//	swap(_pStr, strTemp._pStr);
	//}
	//String& operator=(const String& s)
	//{
	//	if (this != &s)
	//	{
	//		String strTemp(s);
	//		swap(_pStr, strTemp._pStr);
	//	}
	//	return *this;
	//}
	~String()
	{
		if (_pStr)
		{
			delete[] _pStr;
			_pStr = NULL;
		}
	}
	size_t Size()const
	{
		return sizeof(_pStr);
	}
	size_t Lengh()const
	{
		return strlen(_pStr);
	}
	char& operator[](size_t index)
	{
		return _pStr[index];
	}
	const char& operator[](size_t index) const
	{
		return _pStr[index];
	}
	bool operator>(const String& s)
	{
		if (strcmp(_pStr, s._pStr) > 0)
			return true;
		if (strcmp(_pStr, s._pStr) < 0)
			return false;
	}
	bool operator<(const String& s)
	{
		return !(_pStr>s._pStr);
	}
	bool operator==(const String& s)
	{
		if (strcmp(_pStr, s._pStr) == 0)
			return true;
		return false;
	}
	bool operator!=(const String& s)
	{
		return !(_pStr, s._pStr);
	}
	void Copy(const String& s)
	{
		strcpy(_pStr, s._pStr);
	}
	bool strstr(const String& s)
	{

	}
	String& operator+=(const String& s)
	{
		char* dest;
		dest = new char[strlen(s._pStr) + Lengh() + 1];
		memcpy(dest, _pStr, Lengh());
		memcpy(dest + Lengh(), s._pStr, strlen(s._pStr) + 1);
		delete[] _pStr;
		_pStr = dest;
		return *this;
	}
private:
	char* _pStr;
};

//引用计数版本一
//class String
//{
//public:
//	String(const char* pStr = "")
//		:_pCount(new int(1))
//	{
//		if (pStr == NULL)
//		{
//			_pStr = new char[1];
//			*_pStr = '\0';
//		}
//		else
//		{
//			_pStr = new char[strlen(pStr) + 1];
//			strcpy(_pStr, pStr);
//		}
//	}
//	String(const String& s)
//		:_pStr(s._pStr)
//		, _pCount(s._pCount)
//	{
//		++(*_pCount);
//	}
//	String& operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			if (--(*_pCount) == 0)
//			{
//				delete[] _pStr;
//				delete _pCount;
//			}
//			_pStr = s._pStr;
//			_pCount = s._pCount;
//			++(*_pCount);
//		}
//		return *this;
//	}
//	~String()
//	{
//		if (_pStr&&--(*_pCount) == 0)
//		{
//			delete[] _pStr;
//			_pStr = NULL;
//			delete _pCount;
//			_pCount = NULL;
//		}
//	}
//private:
//	char* _pStr;
//	int* _pCount;
//};

//引用计数版本二
//class String
//{
//public:
//	String(const char* pStr = "")
//	{
//		if (pStr == NULL)
//		{
//			_pStr = "";
//		}
//		_pStr = new char[strlen(pStr) + 1 + 4];
//		_pStr += 4;
//		strcpy(_pStr, pStr);
//		GetReference() = 1;
//	}
//	String(const String& s)
//		:_pStr(s._pStr)
//	{
//		++GetReference();
//	}
//	String& operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			Release();
//			_pStr = s._pStr;
//			++GetReference();
//		}
//		return *this;
//	}
//	~String()
//	{
//		Release();
//	}
//private:
//	int& GetReference()
//	{
//		return *(int *)(_pStr - 4);
//	}
//	void Release()
//	{
//		if (_pStr&&--GetReference() == 0)
//		{
//			_pStr -= 4;
//			delete[] _pStr;
//			_pStr = NULL;
//		}
//	}
//private:
//	char* _pStr;
//};

int main()
{
	String s1;
	String s2("hello");
	String s3(s2);
	String s4;
	s4 = s2;
	system("pause");
	return 0;
}