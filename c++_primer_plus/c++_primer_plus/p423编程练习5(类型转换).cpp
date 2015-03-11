// 编程练习 11.9 (5) 英石和英镑之间的转换
#include <iostream>
class Stonewt
{
public:
	enum mode{stn = 's', int_p = 'i', double_p = 'd'};
	mode zhuangtai;  // 自己想的方法

private:
	enum {LBS_per_stn = 14};
	int stone;
	double pds_left;
	double pounds;
	char mode;  // std 方法 's' = stone, 'f' = float, 'w' = whole pounds

public:
	Stonewt();
	Stonewt(double);
	Stonewt(int, double = 0.0);
	~Stonewt() { }
	Stonewt operator+(const Stonewt &) const;
	Stonewt operator-(const Stonewt &) const;
	Stonewt operator*(double) const;
	friend Stonewt operator*(double, const Stonewt &);
	friend std::ostream & operator<<(std::ostream &, const Stonewt &);
	void set_mode(char m) {mode = m;}  // std 方法
};

// 实现文件
Stonewt::Stonewt()
{
	stone = pounds = pds_left = 0;
	zhuangtai = double_p;
}

Stonewt::Stonewt(double d)
{
	stone = d / LBS_per_stn;
	pds_left = int(d) % LBS_per_stn + d - int(d);
	pounds = d;
	zhuangtai = double_p;
}

Stonewt::Stonewt(int i, double d)
{
	pounds = i * LBS_per_stn + d;
	stone = pounds / LBS_per_stn;
	pds_left = int(pounds) % LBS_per_stn + pounds - int(pounds);
	zhuangtai = stn;
}

Stonewt Stonewt::operator+(const Stonewt & s) const
{
	return Stonewt(s.pounds + pounds);
}

Stonewt Stonewt::operator-(const Stonewt & s) const
{
	return Stonewt(pounds - s.pounds);
}

Stonewt Stonewt::operator*(double d) const
{
	return Stonewt(d * pounds);
}

Stonewt operator*(double d, const Stonewt & s)
{
	return s * d;
}

std::ostream & operator<<(std::ostream & os, const Stonewt & s)
{
	if (s.zhuangtai == Stonewt::stn)
		std::cout << s.stone << " stone, " << s.pds_left << " pounds";
	else if (s.zhuangtai == Stonewt::int_p)
		std::cout << int(s.pounds + 0.5) << " pounds";
	else if (s.zhuangtai == Stonewt::double_p)
		std::cout << s.pounds << " pounds";
	else
		std::cout << "无法识别的显示模式.\n";
	return os;
}

// 客户文件
int main()
{
	using std::cout;
	using std::endl;

	Stonewt s1;
	cout << s1 << endl;

	Stonewt s2(222.5);
	cout << s2 << endl;
	s2.zhuangtai = Stonewt::stn;
	cout << s2 << endl;

	Stonewt s3(15, 12.5);
	cout << s3 << endl;
	s3.zhuangtai = Stonewt::double_p;
	cout << s3 << endl;
	s3.zhuangtai = Stonewt::int_p;
	cout << s3 << endl;

	cout << s2 + s3 << endl;
	cout << s2 * 5 - s3 << endl;

	return 0;
}