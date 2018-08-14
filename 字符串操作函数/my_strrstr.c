#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *my_strrstr(const char *s1, const char s2[])
{
	assert(s1);
	assert(s2);
	char* last = NULL;
	char* start = s1;
	int j = 0;
	if(*s2 == 0)
		return 0;
	while (*s1&&*s2)
	{
		start = s1;
		while (*s1&&s2[j] && *s1 == s2[j])
		{
			s1++;
			j++;
		}
		if (s2[j] == '\0')
		{
			last = start;
		}
		s1 = start + 1;
		j = 0;
	}
	if (*s1 == '\0')
		return last;
	else
		return NULL;
	 
}

int main()
{
	const char *arr = "abcdabcdef";
	const char *arr2 = "cd";
	char *ret = my_strrstr(arr, arr2);
	printf("%s\n", ret);
	system("pause");
	return 0;
}
