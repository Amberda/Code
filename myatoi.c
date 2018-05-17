#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

//��������ö�ٳ�������ʾ״̬
enum STATE
{
	VALID,  //�Ϸ�
	INVALID,//�Ƿ�
};
enum STATE state = INVALID;
int my_atoi(const char *str)
{
	int flag = 1;
	long long ret = 0;//����Ϊ��int�洢��Χ��Ҫ������ͣ���ֹ�����ж����ʱ����
	//��ָ��
	assert(str);
	//���ַ���
	if (*str == "\0")
	{
		return 0;
	}
	//�հ��ַ�
	while (isspace(*str))//�ú���isspace�ж��Ƿ�Ϊ�հ��ַ�
	{
		str++;
	}
	//����������
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
		if (isdigit(*str))//�ú���isdigit�ж��Ƿ�Ϊ�����ַ�
		{
			ret = ret * 10 + flag*(*str - '0');
			//�ж��Ƿ����
			if (ret > INT_MAX || ret < INT_MIN)
			{
				return ret;
			}
		}
		//�쳣�ַ�
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
