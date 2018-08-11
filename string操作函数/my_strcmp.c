#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int my_strcmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	return *str1 - *str2;

}
int main()
{
	char *p = "abcde";
	char *q = "addcs";
	int ret = my_strcmp(p, q);
	printf("ret=%d\n", ret);
	system("pause\n");
	return 0;
}
