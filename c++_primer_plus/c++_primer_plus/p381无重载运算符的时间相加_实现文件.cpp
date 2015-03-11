// 程序清单 11.2 实现文件
#include <iostream>
#include "p381无重载运算符的时间相加.h"

Time::Time()
{
	hours = minutes = 0;
}

Time::Time(int h, int m)
{
	hours = h;
	minutes = m;
}

void Time::AddMin(int m)
{
	minutes += m;
	hours += minutes / 60;
	minutes %= 60;
}

void Time::AddHr(int h)
{
	hours += h;
}

void Time::Reset(int h, int m)
{
	hours = h;
	minutes = m;
}

Time Time::Sum(const Time & t) const  // 参数是引用是因为引用传值更加快, 但是返回值不能是引用, 因为创建的局部变量会在函数结束的时候消失所以应该传递值而不是引用
{
	Time sum;
	sum.minutes = this->minutes + t.minutes;  // this-> 完全可以省略
	sum.hours = hours + t.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}

void Time::show() const
{
	std::cout << hours << " hours, " << minutes << " minutes";
}