// 程序清单 11.4 头文件
#include <ostream>
#ifndef MYTIME_H_
#define MYTIME_H_

class Time
{
private:
	int h;
	int m;
public:
	Time();
	Time(int h, int m = 0);
	void AddMin(int m);
	void AddHr(int h);
	void Reset(int h = 0, int m = 0);
	Time operator+(const Time & t) const;  // 不管是+号左右加不加空格都能用
	Time operator*(double)const;
	void show() const;
	friend void operator<<(std::ostream &, Time &);
		// 友元函数与成员函数的区别: 成员函数是类定义的一部分, 通过特定的对象来调用, 成员函数可以隐式的访问调用对象的成员, 而不需要使用成员运算符
							   // 友元函数不是类的组成部分, 因此被称为直接函数调用, 友元函数不能隐式访问类成员, 而必须将成员运算符用于作为参数传递的对象
};

#endif