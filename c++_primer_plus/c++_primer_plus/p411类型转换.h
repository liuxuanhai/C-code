// 程序清单 11.16 头文件
#ifndef STONEWT_H_
#define STONEWT_H_

class Stonewt
{
private:
	enum {LBS_per_stn = 14};  // pounds per stone
	int stone;  // whole stones
	double pds_left;  // fractional(部分的, 分数的, 小数的) pounds
	double pounds;
public:
	Stonewt(double lbs);  // constructor for double pounds
	Stonewt(int stn, double lbs);  // constructor for stone, lbs
	Stonewt();  // default constructor
	void show_lbs() const;  // show weight in pounds(磅) format
	void show_stn() const;  // show weight in stone(英石) format

// conversion functions
	operator int() const;  // 虽然没有声明返回类型, 这两个函数也将返回所需的值
		// 这里的int将会将待转换的值四舍五入为最接近的整数, 而不是去掉小数部分
	operator double() const;

// 复习题 11.8 (1)
	Stonewt operator * (double) const;
// 复习题 11.8 (4)
	friend Stonewt operator * (double d, Stonewt & s)
	{
		return Stonewt(d * s.pounds);
	}
};
#endif