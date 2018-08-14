#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int my_strncmp(char const *s1, char const *s2, size_t len)
{
	assert(s1);
	assert(s2);
	while (len--)
	{
			if (*s1 == *s2)
			{
				s1++;
				s2++;
			}
			else
			{
				return *s1 - *s2;
			}
	}
		return 0;
}
int main()
{
	char *p = "abcde";
	char *q = "abcct";
	int ret = my_strncmp(p, q, 4);
	printf("%d\n", ret);
	system("pause");
	return 0;
}
