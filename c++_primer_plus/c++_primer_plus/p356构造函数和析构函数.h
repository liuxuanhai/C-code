// 程序清单 10.4 头文件
#ifndef STOCK10_H_
#define STOCK10_H_
#include <string>

class Stock
{
private:
	std::string company;
	long shares;
	double share_val;
	double total_val;
	void set_tot(){total_val = shares * share_val;};
public:
// two constructors
	Stock();  // default constructor  // 当且仅当没用定义任何构造函数时, 编译器才会提供默认构造函数, 为类定义了构造函数后, 程序员就必须为他提供默认构造函数, 如果提供了非默认构造函数, 但是没有提供默认构造函数, 则Stock Stock1;类型的声明会报错
		// 定义默认构造函数的方式有两种: 1. 给已有的构造函数所有参数提供默认值   2. 通过函数重载定义另一个构造函数---一个没有参数的构造函数 Stock(); 但是只能又一个构造函数, 因此不能同时使用这两种方法
	Stock(const std::string & co, long n = 0, double pr = 0.0);
	~Stock();  // noisy destructor
	void buy(long num, double price);
	void sell(long num, double price);
	void update(double price);
	void show();
};

#endif