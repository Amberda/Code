#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <cmath>

void guass(double a[100][100], double x[], int h)
{
	int i, j, mk;
	double max, p, w[100];
	for (i = 0; i <= h - 2; i++)
	{
		max = 0;
		mk = i;
		for (j = i; j<h; j++)//ѡ��Ԫ
		{
			if (fabs(a[j][i])>max)
			{
				max = fabs(a[j][i]);
				mk = j;
			}
		}
		if (mk != i)
		{
			for (j = i; j <= h; j++)
			{
				p = a[i][j];
				a[i][j] = a[mk][j];
				a[mk][j] = p;
			}
		}
		//��������ĵ�i�к͵�mk��
		for (j = i + 1; j<h; j++)
		{
			p = a[j][i] / a[i][i];
			for (mk = i; mk <= h; mk++)
			{
				a[j][mk] -= p*a[i][mk];
			}
		}//�Ե�i��Ϊ�����д����i�����¸���
	}
		for (i = 0; i<h; i++)      //���
		{
			w[i] = a[i][h];
		}
		for (i = h - 1; i >= 0; i--)
		{
			for (j = h - 1; j>i; j--)
			{
				w[i] -= a[i][j] * x[j];
			}
			x[i] = w[i] / a[i][i];
		}
}
int main()
{
	double a[100][100];
	int i, j, h0, l0, s = 0;
	double x[100];
	cout << "������������������:";
	cin >> h0;
	cout << "������������������:";
	cin >> l0;
	cout << "�������������:" << endl;
	for (i = 0; i < h0; i++)
	{
		for (j = 0; j < l0; j++)
		{
			cin >> a[i][j];
			cout << endl;
		}
	}
	guass(a, x, h0);//����Guass����Ԫ�㷨����
	cout << "�任����������:" << endl;
	for (i = 0; i<h0; i++)
	{
		for (j = 0; j<l0; j++)
		{
			cout << a[i][j] << " ";
			s = s + 1;
		}
		cout << endl;
		if (s == l0)
			cout << endl;
	}
	cout << "������Ľ�:" << endl;
	for (i = 0; i < h0; i++)
	{
		cout << "x[" << i << "]" << x[i] << endl;
	}
	system("pause");
	return 0;
}   
//void guass(double a[100][100], double x[], int h)
//{
//	int i, j, mk;
//	double max, p, w[100];
//	for (i = 0; i <= h - 2; i++)
//	{
//		max = 0;
//		mk = i;
//		for (j = i; j<h; j++)//ѡ��Ԫ
//		{
//			if (fabs(a[j][i])>max)
//			{
//				max = fabs(a[j][i]); mk = j;
//			}
//		}
//		if (mk != i)
//		{
//			for (j = i; j <= h; j++)
//			{
//				p = a[i][j]; a[i][j] = a[mk][j]; a[mk][j] = p;
//			}//��������ĵ�i�к͵�mk��
//		}
//		for (j = i + 1; j<h; j++)
//		{
//			p = a[j][i] / a[i][i];
//			for (mk = i; mk <= h; mk++)
//			{
//				a[j][mk] -= p*a[i][mk];
//			}
//		}//�Ե�i��Ϊ�����д����i�����¸���
//	}
//
//	for (i = 0; i<h; i++)      //���
//	{
//		w[i] = a[i][h];
//	}
//	for (i = h - 1; i >= 0; i--)
//	{
//		for (j = h - 1; j>i; j--)
//		{
//			w[i] -= a[i][j] * x[j];
//		}
//		x[i] = w[i] / a[i][i];
//	}
//}
//int main()
//{
//	double a[100][100];
//	int i, j, h0, l0, s = 0;
//	double x[100];
//	cout << "������������������:";
//	cin >> h0;
//	cout << "������������������:";
//	cin >> l0;
//	cout << "�������������:" << endl;
//	for (i = 0; i < h0; i++)
//	{
//		for (j = 0; j < l0; j++)
//		{
//			cin >> a[i][j];
//			cout << endl;
//		}
//	}
//	guass(a, x, h0);//����Guass����Ԫ�㷨����
//	cout << "�任����������:" << endl;
//	for (i = 0; i<h0; i++)
//	{
//		for (j = 0; j<l0; j++)
//		{
//			cout << a[i][j] << " ";
//			s = s + 1;
//		}
//		if (s == l0)
//		{
//			cout << endl;
//		}
//	}
//	cout << "������Ľ�:" << endl;
//	for (i = 0; i < h0; i++)
//	{
//		cout << "x[" << i << "]" << x[i] << endl;
//	}
//	system("pause");
//	return 0;
//
//}
