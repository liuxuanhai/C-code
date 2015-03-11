// 程序清单 11.5 实现文件
#include <iostream>
#include "p384运算符重载实现时间相加.h"

Time::Time()
{
	h = m = 0;
}

Time::Time(int h_, int m_)
{
	h = h_;
	m = m_;
}

void Time::AddMin(int m_)
{
	m += m_;
	h += m_ / 60;
	m %= 60;
}

void Time::AddHr(int h_)
{
	h += h_;
}

void Time::Reset(int h_, int m_)
{
	h = h_;
	m = m_;
}

Time Time::operator+(const Time & t) const
{
	Time sum;
	sum.m = m + t.m;
	sum.h = h + t.h + sum.m / 60;
	sum.m %= 60;
	return sum;
}

Time Time::operator*(double mult) const
{
	Time result;
	long totalminutes = h * mult * 60 + m * mult;
	result.h = totalminutes / 60;
	result.m = totalminutes % 60;
	return result;
}

Time operator*(double d, const Time & t)
{
	return t * d;
}

void Time::show() const
{
	std::cout << h << " hours, " << m << "minutes.";
}

void operator<<(std::ostream & os, Time & t)
{
	std::cout << t.h << " hours, " << t.m << "minutes.";
}