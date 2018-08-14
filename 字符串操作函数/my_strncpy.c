#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *my_strncpy(char *dest, const char *src, size_t len)
{
	char *ret = dest;
	size_t i = 0;
	assert(dest);
	assert(src);
	while (len--)
	{
		*ret++ = *src++;
	}
	if (*(ret) != '\0')
	{
		*ret = '\0';
	}
	return dest;
}
int main()
{
	char arr[] = "hello bit";
	char arr2[20];
	my_strncpy(arr2, arr, 5);
	printf("%s", arr2);
	system("pause");
	return 0;
}
