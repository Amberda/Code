#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *my_strncat(char *dst, const char *src, size_t len)
{
	char *ret = dst;
	assert(dst);
	assert(src);
	while (*dst != '\0')
	{
		dst++;
	}
	while (len--)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return ret;
}
int main()
{
	char p[20] = "hello ";
	char *q = "world";
	my_strncat(p, q, 3);
	printf("%s", p);
	system("pause");
	return 0;
}
