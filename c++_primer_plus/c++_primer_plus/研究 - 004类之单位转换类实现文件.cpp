#include "研究 - 004类之单位转换类.h"
#include <iostream>
using std::cout;

Stonewt::Stonewt(double lbs)
{
	stone		= int(lbs) / Lbs_per_stn;
										 // 取出小数部分
	pds_left	= int(lbs) % Lbs_per_stn + lbs - int(lbs);
	pounds		= lbs;
}

Stonewt::Stonewt(int stn, double lbs)
{
	//pounds		= stn * Lbs_per_stn;
	//stone		= stn;
	//pds_left	= lbs;	// 这里的lbs如果给大了不用转换成stone???  书中代码好像错了
	pounds		= stn * Lbs_per_stn + lbs;
	stone		= pounds / Lbs_per_stn;
	pds_left	= (int)pounds % Lbs_per_stn + pounds - int(pounds);
}

Stonewt::Stonewt()
{
	stone = pounds = pds_left = 0;
}

Stonewt::~Stonewt()
{
	cout << pounds << "被释放\n";
}

void Stonewt::show_stn() const
{
	cout << stone << " stone, " << pds_left << " pounds\n";
}

void Stonewt::show_lbs() const
{
	cout << pounds << " pounds\n";
}