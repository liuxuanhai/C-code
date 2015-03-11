// 程序清单 11.14
#include <cmath>
#include "p400矢量类.h"
using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;
using std::cout;

namespace VECTOR
{
	// compute degree in one radian
	const double Rad_to_deg = 45.0 / atan(1.0);  // shuold be about 57.2957795130823

	// private methods
	// calculates magnitude from x and y
	void Vector::set_mag()
	{
		mag = sqrt(x * x + y * y);
	}

	void Vector::set_ang()
	{
		if (x == 0.0 && y == 0.0)
			ang = 0.0;
		else
			ang = atan2(y, x);
	}

	// set x from polar coordinate
	void Vector::set_x()
	{
		x = mag * cos(ang);
	}

	// set y from polar coordinate
	void Vector::set_y()
	{
		y = mag * sin(ang);
	}

// public methods
	Vector::Vector()  // default constructor
	{
		x = y = mag = ang = 0.0;
		mode = RECT;
	}

	// constructor vector from rectangular coordinates if form is r
	// (the default) or else from polar coordinates if form is p
	Vector::Vector(double n1, double n2, Mode form)
	{
		mode = form;
		if (form == RECT)
		{
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == POL)
		{
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else
		{
			cout << "Incorrect 3rd argument to Vector() -- ";
			cout << "vector set to 0\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	void Vector::reset(double n1, double n2, Mode form)
	{
		mode = form;
		if (form == RECT)
		{
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == POL)
		{
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else
		{
			cout << "Incorrect 3rd argument to Vector() -- ";
			cout << "vector set to 0\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	Vector::~Vector()  // destructor
	{
	}

	void Vector::polar_mode()  // set to polar mode
	{
		mode = POL;
	}

	void Vector::rect_mode()  // set to rectangular mode
	{
		mode = RECT;
	}

	// operator overloading
	// add two Vectors
	Vector Vector::operator+(const Vector & b) const
	{
		return Vector(x + b.x, y + b.y);  // 如果方法通过计算得到一个新的对象, 则应考虑是否可以使用类构造函数来完成这种工作. 这样做不仅可以避免麻烦, 而且可以确保新的对象是按照正确的方式创建的
	}

	// subtract Vector b from a
	Vector Vector::operator-(const Vector & b) const
	{
		return Vector(x - b.x, y - b.y);
	}

	// reverse sign of Vector
	Vector Vector::operator-() const  // 重载的一元符号运算符, 他返回一个与原来矢量相反的矢量
								// 但是对于只有二元形式的运算符只能将其重载为二元运算符
	{
		return Vector(-x, -y);
	}

	// multiply vector by n
	Vector Vector::operator*(double n) const
	{
		return Vector(n * x, n * y);
	}

	// friend methods
	// multiply n by Vector a
	Vector operator*(double n, const Vector & a)
	{
		return a * n;
	}

	// display rectangulai coordinates if mode is RECT,
	// else display polar coordinates if mode is POL
	std::ostream & operator<<(std::ostream & os, const Vector & v)
	{
		if (v.mode == Vector::RECT)  // 这是一个友元函数, 它不在类作用域内, 因此必须使用Vector::RECT, 而不能直接使用RECT, 但是这个友元函数在名称空间VRCTOR中, 因此无需使用全限定名VECTOR::Vector::RECT
			os << "(x, y) = ("<< v.x << ", " << v.y << ")";
		else if (v.mode == Vector::POL)
		{
			os << "(m, a) = (" << v.mag << ", "
				<< v.ang * Rad_to_deg << ")";
		}
		else
			os << "Vector object mode is invalid";
		return os;
	}

}