// 程序清单 11.17 实现文件
#include <iostream>
using std::cout;
#include "p411类型转换.h"

Stonewt::Stonewt(double lbs)
{
	stone = int (lbs) / LBS_per_stn;
	pds_left = int (lbs) % LBS_per_stn + lbs - int(lbs);
	pounds = lbs;
}

Stonewt::Stonewt(int stn, double lbs)
{
	stone = stn;
	pds_left = lbs;
	pounds = stn * LBS_per_stn + lbs;
}

Stonewt::Stonewt()
{
	stone = pounds = pds_left = 0;
}

void Stonewt::show_stn() const
{
	cout << stone << " stone, " << pds_left << " pounds\n";
}

void Stonewt::show_lbs() const
{
	cout << pounds << " pounds\n";
}

// conversion functions
Stonewt::operator int() const
{
	return int (pounds + 0.5);  // 四舍五入的实现方法
}

Stonewt::operator double() const
{
	return pounds;
}

// 复习题 11.8 (1)
Stonewt Stonewt::operator * (double d) const
{
	return Stonewt(d * pounds);
}