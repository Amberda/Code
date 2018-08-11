#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

char *my_strchr(char const *str, int ch)
{
	const char *tmp = str;
	while (*tmp)
	{
		if (*tmp == ch)
		{
			return tmp;
		}
		tmp++;
	}
	return NULL;
}
int main()
{
	char arr[] = "hello world";
	char *ret = my_strchr(arr, 'l');
	printf("%s\n", ret);
	system("pause");
	return 0;
}
