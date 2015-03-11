#include <iostream>
#include "研究 - 001类之股票类.h"

//void Stock::acquire(const std::string & co, long n, double pr)
//{
//	company = co;
//	
//	if (n < 0)
//	{
//		std::cout << "股票数不能设置为负数, 自动将" << company << "公司的股票数设置成0!\n";
//		shares = 0;
//	}
//	else
//		shares = n;
//
//	share_val = pr;
//	set_tot();
//}
	// 构造函数替换acquire函数, 用来初始化对象
Stock::Stock(const std::string & co, long n, double pr)
{
	company = co;
	
	if (n < 0)
	{
		std::cout << "股票数不能设置为负数, 自动将" << company << "公司的股票数设置成0!\n";
		shares = 0;
	}
	else
		shares = n;

	share_val = pr;
	set_tot();
}

Stock::Stock(void)
{
	std::cout << "默认构造函数被调用!\n";

	company		= "No Name";
	shares		= 0;
	share_val	= 0;
	total_val	= 0;
}

Stock::~Stock()
{
	std::cout << company << "析构函数被调用!\n";
}

void Stock::buy(long num, double price)
{
	if (num < 0)
		std::cout << "您的购买不能是负数, 交易失败!\n";
	else
	{
		shares	   += num;
		share_val	= price;
		set_tot();
	}
}

void Stock::sell(long num, double price)
{
	if (num < 0)
		std::cout << "您的售出不能为负数, 交易失败!\n";
	else if (num > shares)
		std::cout << "您的持有量少于您想要售出的数量, 交易失败!\n";
	else
	{
		shares	   -= num;
		share_val	= price;
		set_tot();
	}
}

void Stock::update(double price)
{
	share_val = price;
	set_tot();
}

void Stock::show(void) const
{
	using std::cout;
	using std::ios_base;

		// 将格式设置成 #.###
	ios_base::fmtflags	orig		= cout.setf(ios_base::fixed, ios_base::floatfield);
	std::streamsize		prec		= cout.precision(3);

	cout << "公司: " << company
		 << "	股数: " << shares << std::endl;
	cout << "	股价: $" << share_val;

		// 将格式设置成 #.##
	cout.precision(2);
	cout << "	总价值: $" << total_val << std::endl;
			
		// 将输出格式还原
	cout.setf(orig, ios_base::floatfield);
	cout.precision(prec);
}

const Stock Stock::GetBigger(const Stock & s) const
{
	if (s.total_val > this->total_val)	// 这里可以直接写成s.total_val, 说明在这里可以直接访问私有数据
		return s;
	else
		return *this;
}