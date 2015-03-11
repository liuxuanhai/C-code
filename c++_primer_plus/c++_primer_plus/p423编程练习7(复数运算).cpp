// 编程练习 11.9 (7) 复数
#include <iostream>
class Complex
{
private:
	double shi;
	double xu;

public:
	Complex();
	Complex(double, double = 0.0);
	Complex operator+(const Complex &) const;
	Complex operator-(const Complex &) const;
	Complex operator*(const Complex &) const;
	Complex operator*(double) const;
	friend Complex operator*(double, const Complex &);
	Complex operator~() const;
	friend std::ostream & operator<<(std::ostream &, const Complex &);
	friend std::istream & operator>>(std::istream &, Complex &);
};

Complex::Complex()
{
	shi = 0.0;
	xu = 0.0;
}

Complex::Complex(double shi_, double xu_)
{
	shi = shi_;
	xu = xu_;
}

Complex Complex::operator+(const Complex & c) const
{
	return Complex(c.shi + shi, c.xu + xu);
}

Complex Complex::operator-(const Complex & c) const
{
	return Complex(shi - c.shi, xu - c.xu);
}

Complex Complex::operator*(const Complex & c) const
{
	return Complex(c.shi * shi - c.xu * xu, shi * c.xu + xu * c.shi);
}

Complex operator*(double d, const Complex & c)
{
	return Complex(d * c.shi, d * c.xu);
}

Complex Complex::operator~() const
{
	return Complex(shi, -xu);
}

std::ostream & operator<<(std::ostream & os, const Complex & c)
{
	os << "(" << c.shi << ", " << c.xu << "i)";
	return os;
}

std::istream & operator>>(std::istream & is, Complex & c)
{
	std::cout << "实数部分:\n";
	is >> c.shi;
	if (is)
	{
		std::cout << "虚数部分:\n";
		is >> c.xu;	
	}
	return is;
}

int main()
{
	using namespace std;
	Complex a(3.0, 4.0);
	Complex c;
	cout << "Enter a complex number (q to quit):\n";
	while (cin >> c)
	{
		cout << "c is " << c << '\n';
		cout << "complex conjugate(~c) is " << ~c << '\n';
		cout << "a is " << a << '\n';
		cout << "a + c is " << a + c << '\n';
		cout << "a - c is " << a - c << '\n';
		cout << "a * c is " << a * c << "\n";
		cout << "2 * c is " << 2 * c << '\n';
		cout << "Enter a complex number (q to quit): \n";
	}
	cout << "Done!\n";

	return 0;
}