#include <iostream>

	// Stonewt 类声明

class Stonewt
{
public: 
	enum {StoneToPounds = 14};
	enum enumFlag{enumStone, enumStonePound, enumPounds};
private:
	double stone_;
	double stone_pound_stn_;
	double Stone_pound_pd_;
	double pounds_;	// 默认
	enumFlag flag_;
	enumFlag showFlag_;

	void SetStone(){stone_ = pounds_ / StoneToPounds;}
	void SetStonePound(){stone_pound_stn_ = (int)pounds_ / 14; Stone_pound_pd_ = (int)pounds_ % StoneToPounds + pounds_ - (int)pounds_;}

public:
	Stonewt(){stone_ = stone_pound_stn_ = Stone_pound_pd_ = pounds_ = 0; showFlag_ = enumPounds;}
	explicit Stonewt(double, enumFlag = enumPounds);
	Stonewt(double stn, double pd){pounds_ = stn * StoneToPounds; showFlag_ = enumPounds; SetStone(); SetStonePound();}

	friend std::ostream & operator<<(std::ostream & os, const Stonewt & s);
	const Stonewt operator+(const Stonewt & rs) const {Stonewt temp; temp.pounds_ = this->pounds_ + rs.pounds_; temp.SetStone(); temp.SetStonePound(); return temp;}
	friend const Stonewt operator+(const double db, const Stonewt & s){Stonewt temp; temp.pounds_ = db + s.pounds_;temp.SetStone(); temp.SetStonePound(); return temp;}
	const Stonewt operator+(double db){return db + *this;}
	
	void SetShowFlag(enumFlag flag){showFlag_ = flag;}
};

int main(void)
{
	using std::cout;
	using std::cin;
	using std::endl;

/**************** 测试<<的不同输出 ***********************/
	cout << "s:\n";
	Stonewt s(123.45);
	cout << s << endl;
	s.SetShowFlag(s.enumStone);
	cout << s << endl;
	s.SetShowFlag(s.enumStonePound);
	cout << s << endl;
/**************** 测试运算符重载 **************************/
	cout << "ss:\n";
	Stonewt ss(56.1, Stonewt::enumStone);
	cout << ss << endl;
	cout << "s + ss:\n\t" << s + ss << endl;
	cout << "s + 11.22:\n\t" << s + 11.22 << endl;
	cout << "11.22 + s:\n\t" << 11.22 + s << endl;

	return 0;
}

Stonewt::Stonewt(double db, enumFlag flag)
{
	showFlag_ = enumPounds;
	if (flag == enumPounds)
	{
		pounds_ = db;
		SetStonePound();
		SetStone();
	}
	else if (flag == enumStone)
	{
		pounds_ = db * StoneToPounds;
		SetStonePound();
		SetStone();
	}
	else
		std::cout << "Stonewt::Stonewt(double db, enumFlag flag)设计错误!\n";
}

std::ostream & operator<<(std::ostream & os, const Stonewt & s)
{
	if (s.showFlag_ == Stonewt::enumPounds)
		std::cout << "Pounds: " << s.pounds_;
	else if (s.showFlag_ == s.enumStone)
		std::cout << "Stones: " << s.stone_;
	else if (s.showFlag_ == s.enumStonePound)
		std::cout << s.stone_pound_stn_ << " Stones, " << s.Stone_pound_pd_ << "Pounds.";
	else
		std::cout << "Error: 重载<<出现了没有输出flag!\n";
	return os;
}