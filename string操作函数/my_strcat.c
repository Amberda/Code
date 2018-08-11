#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *my_strcat(char *dest, const char *src)
{
	char *ret = dest;
	assert(dest);
	assert(src);
	while (*dest != '\0')
	{
		dest++;
	}
	while (*dest++ = *src++)
	{
		;
	}
	return ret;
}
int main()
{
	char arr[20] = "hello ";
	my_strcat(arr, "bit.");
	printf("%s\n", arr);
	system("pause\n");
	return 0;
}
