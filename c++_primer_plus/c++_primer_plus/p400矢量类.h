// 程序清单 11.13 头文件
#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
namespace VECTOR
{
	class Vector
	{
	public:
		enum Mode {RECT, POL};  // RECT for rectangualr, POL for Polar modes
			// RECT 直角坐标模式(默认值), POL 极坐标模式
	private:
		double x;
		double y;
		double mag;  // length of vector
		double ang;  // direction of vector in degrees
		Mode mode;  // RECT or POL
	// private methods for setting values
		void set_mag();
		void set_ang();
		void set_x();
		void set_y();
	public:
		Vector();
		Vector(double, double, Mode form = RECT);
		void reset(double, double, Mode form = RECT);
		~Vector();
		double xval() const {return x;};  // report x value
		double yval() const {return y;};  // report y value
		double magval() const {return mag;};  // report magnitude
		double angval() const {return ang;};  // report angle
		void polar_mode();  // set mode to POL
		void rect_mode();  // set mode to RECT
	// operator overloading
		Vector operator+(const Vector & b) const;
		Vector operator-(const Vector & b) const;
		Vector operator-() const;
		Vector operator*(double n) const;
	// friends
		friend Vector operator*(double, const Vector &);
		friend std::ostream &
			operator<<(std::ostream &, const Vector &);
	};
}
#endif