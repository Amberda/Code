#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

//定义两个枚举常量来表示状态
enum STATE
{
	VALID,  //合法
	INVALID,//非法
};
enum STATE state = INVALID;
int my_atoi(const char *str)
{
	int flag = 1;
	long long ret = 0;//定义为比int存储范围还要大的类型，防止后面判断溢出时出错。
	//空指针
	assert(str);
	//空字符串
	if (*str == "\0")
	{
		return 0;
	}
	//空白字符
	while (isspace(*str))//用函数isspace判断是否为空白字符
	{
		str++;
	}
	//遇到正负号
	if (*str == '-')
	{
		flag = -1;
		str++;
	}
	if (*str == '+')
	{
		str++;
	}
	//
	while (*str)
	{
		//if (*str >= '0'&&*str <= '9')
		if (isdigit(*str))//用函数isdigit判断是否为数字字符
		{
			ret = ret * 10 + flag*(*str - '0');
			//判断是否溢出
			if (ret > INT_MAX || ret < INT_MIN)
			{
				return ret;
			}
		}
		//异常字符
		else
		{
			break;
		}
		str++;
	}
	state = VALID;
	return ret;
}
int main()
{
	char *p = "12345";
	char *q = "  -12345";
	int ret = my_atoi(p);
	int ret2 = my_atoi(q);
	printf("%d\n", ret);
	printf("%d\n", ret2);
	system("pause");
	return 0;
}
