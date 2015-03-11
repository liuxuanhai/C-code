// 编程练习 11.9 (2) 矢量类
#ifndef BIANCHENGLIANXI2_H_
#define BIANCHENGLIANXI2_H_
#include <iostream>

namespace VECTOR
{
	class Vector
	{
	private:
		double x;
		double y;
		char mode;  // 'r' = rectangular, 'p' = polar

		void set_x(double, double mag);  // mag 的值是弦度值, 在类中的传递默认也是这样
		void set_y(double, double);

	public:
		Vector();
		Vector(double, double, char = 'r');
		void set(double, double, char = 'r');
		~Vector();
		double xval() const {return x;}
		double yval() const {return y;}
		double magval() const;  // report magnitude
		double angval() const;  // report angle
		void polar_mode();  // set mode to 'p'
		void rect_mode();  // set mode to 'r'
		Vector operator+(const Vector &) const;
		Vector operator-(const Vector &) const;
		Vector operator-() const;  // 一个操作数的是负号, 让x, y同时变成-x, -y
		Vector operator*(double) const;
		friend Vector operator*(double, const Vector &);
		friend std::ostream & operator<<(std::ostream &, const Vector &);
	};
}  // end of namespace VECTOR

#endif

// 实现部分
#include <cmath>

namespace VECTOR
{
	const double Rad_to_deg = 45.0 / atan(1);

	void Vector::set_x(double mag, double ang)
	{
		x = mag * cos(ang);
	}

	void Vector::set_y(double mag, double ang)
	{
		y = mag * sin(ang);
	}

	Vector::Vector()  
	{
		x = y = 0.0;
		mode = 'r';
	}

	Vector::Vector(double n1, double n2, char form)
	{
		mode = form;
		if ('r' == form)
		{
			x = n1;
			y = n2;
		}
		else if ('p' == form)
		{
			set_x(n1, n2 / Rad_to_deg);
			set_y(n1, n2 / Rad_to_deg);
		}
		else
		{
			std::cout << "Incorrect 3rd argument to Vector() -- ";
			std::cout << "vector set to 0.\n";
			x = y = 0.0;
			mode = 'r';
		}
	}

	void Vector::set(double n1, double n2, char form)
	{
		mode = form;
		if (form == 'r')
		{
			x = n1;
			y = n2;
		}
		else if ('p' == form)
		{
			set_x(n1, n2 / Rad_to_deg);
			set_y(n1, n2 / Rad_to_deg);
		}
		else
		{
			std::cout << "Incorrect 3rd argument to Vector() -- ";
			std::cout << "vector set to 0.\n";
			x = y = 0.0;
			mode = 'r';
		}
	}
	
	Vector::~Vector()
	{
	}

	double Vector::magval() const
	{
		return sqrt(x*x + y*y);
	}

	double Vector::angval() const
	{
		if (x == 0.0 && y == 0.0)  // 这个什么用???
			return 0;
		else
			return atan2(y, x);
	}

	void Vector::polar_mode()
	{
		mode = 'p';
	}

	void Vector::rect_mode()
	{
		mode = 'r';
	}

	Vector Vector::operator+(const Vector & b) const
	{
		return Vector(x + b.x, y + b.y);
	}

	Vector Vector::operator-(const Vector & b) const
	{
		return Vector(x - b.x, y - b.y);
	}

	Vector Vector::operator-() const
	{
		return Vector(-x, -y);
	}

	Vector Vector::operator*(double n) const
	{
		return Vector(n * x, n * y);
	}

	// friend methods
	Vector operator*(double n, const Vector & a)
	{
		return a * n;  // ######这是个重点###########
	}

	std::ostream & operator<<(std::ostream & o, const Vector & v)
	{
		if (v.mode == 'r')
			o << "(x, y) = (" << v.x << ", " << v.y << ")";
		else if (v.mode == 'p')
		{
			o << "(m, a) = (" << v.magval() << ", "
				<< v.angval() * Rad_to_deg << ")";
		}
		else
			o << "Vector object mode is invalid";

		return o;
	}
}  // end namespace VECTOR

// 客户文件
#include <cstdlib>  // rand(), srand() prototypes
#include <ctime>  // time() prototype

int main()
{
	using namespace std;
	using VECTOR::Vector;
	srand(time(0));
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;

	cout << "Enter target distance (q to quit): ";
	while (cin >> target)
	{
		cout << "Enter step length: ";
		if (!(cin >> dstep))
			break;

		while (result.magval() < target)
		{
			direction = rand() % 360;
			step.set(dstep, direction, 'p');
			result = result + step;
			steps++;
		}
		cout << "After " << steps << " steps, the subject "
			"has the following location:\n";
		cout << result << endl;
		result.polar_mode();
		cout << "or\n" << result << endl;
		cout << "Average outward distance per step = "
			<< result.magval() / steps << endl;
		steps = 0;
		result.set(0.0, 0.0);
		cout << "Enter target distance (q to quit):";
	}
	cout << "Bye!\n";
	return 0;
}
