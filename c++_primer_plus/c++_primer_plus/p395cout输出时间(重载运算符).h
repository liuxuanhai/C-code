// 程序清单 11.10 头文件
#ifndef MYTIME___
#define MYTIME___
#include <iostream>

class Time
{
private:
	int hours;
	int minutes;
public:
	Time();
	Time(int h, int m = 0);
	void AddMin(int m);
	void AddHr(int h);
	void Reset(int h = 0, int m = 0);
	Time operator+(const Time & t) const;
	Time operator-(const Time & t) const;
	Time operator*(double n) const;
	friend Time operator*(double m, const Time & t)
	{return t * m;}  // inline definition
	friend std::ostream & operator<<(std::ostream & os, const Time & t);
};

#endif