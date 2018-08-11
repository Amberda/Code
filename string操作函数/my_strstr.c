#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *my_strstr(const char*str, const char *substr)
{
	const char *s1 = str;
	const char *s2 = substr;
	const char *cur = str;
	assert(str);
	assert(substr);
	if (*substr == '\0')
		return str;
	while (*cur)
	{
		s1 = cur;
		s2 = substr;
		while (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		if (*s2 == '\0')
			return cur;
		if (*s1 == '\0')
			return NULL;
		cur++;
	}
	return NULL;
}
int main()
{
	char *p1 = "abcdef";
	char *p2 = "def";
	char *ret = my_strstr(p1, p2);
	printf("%s\n", ret);
	system("pause\n");
	return 0;
}
