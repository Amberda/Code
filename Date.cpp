#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdlib.h>
using namespace std;

class Date
{
	//重载输出运算符
	friend ostream& operator<<(ostream& _cout, const Date d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}
public:
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
		//输入日期的合法性判断
	{
		if (!((year > 0) && (month > 0 && month < 13) && (day > 0 && day <= GetMonthDays(_month))))
		{
			//不合法日期自动变成1990-1-1
			_year = 1900;
			_month = 1;
			_day = 1;
		}
	}
	//拷贝构造
	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{}
	//判断是否为闰年
	bool IsLeapYear()
	{
		if (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0))
		{
			return true;
		}
		return false;
	}
	//赋值运算符重载
	Date& operator=(const Date& d)
	{
		if (this != &d);
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
	//一个日期加上一个天数
	Date operator+(int day)
	{
		if (day < 0)//天数若为负数变为减
		{
			return *this - (0 - day);
		}
		Date temp(*this);
		temp._day += day;
		int daysInMonth = temp.GetMonthDays(temp._month);
		while (temp._day>daysInMonth)
		{
			temp._day -= daysInMonth;
			temp._month += 1;
			if (temp._month > 12)
			{
				temp._year += 1;
				temp._month = 1;
			}
		}
		return temp;
	}
	//一个日期减去一个天数
	Date operator-(int day)
	{
		if (day < 0)//天数若为负数变为加
		{
			return *this + (0 - day);
		}
		Date temp(*this);
		temp._day -= day;
		while (temp._day <= 0)
		{
			temp._month--;
			if (temp._month <= 0)
			{
				temp._year--;
				temp._month = 12;
			}
			temp._day += temp.GetMonthDays(temp._month);
		}
		return temp;
	}
	//前置++
	Date operator++()
	{
		*this = *this + 1;
		//_day += 1;
		return *this;
	}
	//后置++
	Date operator++(int)
	{
		Date temp(*this);
		*this = *this + 1;
		return temp;
	}
	//前置--
	Date operator--()
	{
		*this = *this - 1;
		return *this;
	}
	//后置--
	Date operator--(int)
	{
		Date temp(*this);
		*this = *this - 1;
		return temp;
	}
	//两个日期之间间隔的天数
	int operator-(const Date& d)
	{
		Date maxdate(*this);
		Date mindate(d);
		if (maxdate < mindate)
		{
			maxdate = mindate;
			mindate = *this;
		}
		int count = 0;
		while (mindate < maxdate)
		{
			mindate = mindate + 1;
			++count;
		}
		return count;
	}
	//判断两个日期相等
	bool operator==(const Date& d)
	{
		if ((_year == d._year) && (_month == d._month) && (_day == d._day))
		{
			return true;
		}
		return false;
	}
	//判断两个日期不相等
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}
	//比较大小
	bool operator>(const Date& d)
	{
		if ((_year > d._year) || ((_year == d._year) && (_month > d._month))
			|| ((_year == d._year) && (_month == d._month) && (_day > d._day)))
		{
			return true;
		}
		return false;
	}
	//比较大小
	bool operator<(const Date& d)
	{
		return !(*this>d || *this == d);
	}
private:
	//获取每个月的天数
	int GetMonthDays(int month)
	{
		int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (IsLeapYear() && (2 == month))//在这里改变2月的天数
		{
			days[month] += 1;
		}
		return days[month];
	}
	int _year;
	int _month;
	int _day;
};

void FunTest()
{
	Date d1(1900, 2, 28);
	cout << ++d1 << endl;
	cout << --d1 << endl;
	cout << d1 << endl;

	cout << d1-- << endl;
	cout << d1++ << endl;
	cout << d1 << endl;

	Date d2(2017, 5, 1);
	cout << d2 + 100 << endl;
	Date d3(1997, 11, 1);
	cout << d3 - 100 << endl;

	cout << boolalpha << (Date(2016, 10, 1) < d1) << endl;
	cout << d1 - d2 << endl;
}
int main()
{
	FunTest();
	system("pause\n");
	return 0;
}
