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
		for (j = i; j<h; j++)//选主元
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
		//交换矩阵的第i行和第mk行
		for (j = i + 1; j<h; j++)
		{
			p = a[j][i] / a[i][i];
			for (mk = i; mk <= h; mk++)
			{
				a[j][mk] -= p*a[i][mk];
			}
		}//以第i行为工具行处理第i行以下各行
	}
		for (i = 0; i<h; i++)      //求解
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
	cout << "请输入增广矩阵的行数:";
	cin >> h0;
	cout << "请输入增广矩阵的列数:";
	cin >> l0;
	cout << "请输入增广矩阵:" << endl;
	for (i = 0; i < h0; i++)
	{
		for (j = 0; j < l0; j++)
		{
			cin >> a[i][j];
			cout << endl;
		}
	}
	guass(a, x, h0);//调用Guass列主元算法函数
	cout << "变换后的增广矩阵:" << endl;
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
	cout << "方程组的解:" << endl;
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
//		for (j = i; j<h; j++)//选主元
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
//			}//交换矩阵的第i行和第mk行
//		}
//		for (j = i + 1; j<h; j++)
//		{
//			p = a[j][i] / a[i][i];
//			for (mk = i; mk <= h; mk++)
//			{
//				a[j][mk] -= p*a[i][mk];
//			}
//		}//以第i行为工具行处理第i行以下各行
//	}
//
//	for (i = 0; i<h; i++)      //求解
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
//	cout << "请输入增广矩阵的行数:";
//	cin >> h0;
//	cout << "请输入增广矩阵的列数:";
//	cin >> l0;
//	cout << "请输入增广矩阵:" << endl;
//	for (i = 0; i < h0; i++)
//	{
//		for (j = 0; j < l0; j++)
//		{
//			cin >> a[i][j];
//			cout << endl;
//		}
//	}
//	guass(a, x, h0);//调用Guass列主元算法函数
//	cout << "变换后的增广矩阵:" << endl;
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
//	cout << "方程组的解:" << endl;
//	for (i = 0; i < h0; i++)
//	{
//		cout << "x[" << i << "]" << x[i] << endl;
//	}
//	system("pause");
//	return 0;
//
//}
