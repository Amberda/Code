#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdlib.h>
using namespace std;


class Complex
{
public:
	Complex(double real = 0.0, double image = 0.0)
		:_real(real)
		, _image(image)
	{}
	Complex(const Complex& c)
	{

	}
	Complex& operator=(const Complex& c)
	{
		cout << this << "=" << &c << endl;
		if (this != &c)
		{
			_real = c._real;
			_image = c._image;
		}
		return *this;
	}
	Complex operator+(const Complex& c)
	{
		Complex ret = (_real + c._real, _image + c._image);
		return ret;
	}
	Complex operator-(const Complex& c)
	{
		return Complex(_real - c._real, _image - c._image);
	}
	//复数相乘(a+bi)*(c+di)=(ac-bd)+(ad+bc)i
	Complex operator*(const Complex& c)
	{
		return Complex((_real*c._real) - (_image*c._image), (_real + c._image) + (_image + c._image));
	}
	//复数相除(a+bi)/(c+di)=(ac+bd)/(c^2+d^2)+(bc-ad)i/(c^2+d^2)
	Complex operator/(const Complex& c)
	{
		return Complex((_real*c._real) + (_image*c._image)\
			       /(c._real*c._real + c._image*c._image))\
			        , ((_image*c._real) - (_real*c._image)\
			     / (c._real*c._real) + (c._image*c._image));
	}
	Complex operator+=(const Complex& c)
	{
		_real = this->_real + c._real;
		_image = this->_image + c._image;
		return *this;
	}
	Complex operator-=(const Complex& c)
	{
		_real = this->_real - c._real;
		_image = this->_image - c._image;
		return *this;
	}
	Complex operator*=(const Complex& c)
	{
		_real = (this->_real*c._real) - (this->_image*c._image);
		_image = (this->_real*c._image) + (this->_image + c._image);
		return *this;
	}
	Complex operator/=(const Complex& c)
	{
		_real = (this->_real*c._real) + (this->_image*c._image) / (c._real*c._real + c._image*c._image);
		_image = (this->_image*c._real - this->_real*c._image) / (c._real*c._real - c._image*c._image);
		return *this;
	}
	~Complex()
	{}

private:
	double _real;
	double _image;
};

int main()
{
	system("pause\n");
	return 0;
}
