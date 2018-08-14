#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char* my_strrchr(const char* str, int ch)
{
	char* pos = 0;
	assert(str);
	while (*str)
	{
		if (*str == ch)
		{
			pos = str;
		}
		str++;
	}
	if (pos != 0)
	{
		return pos;
	}
	else
		return NULL;
}
int main()
{
	char arr[] = "hello world";
	printf("%s\n", my_strrchr(arr, 'o'));
	system("pause");
	return 0;
}
