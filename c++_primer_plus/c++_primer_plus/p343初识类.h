// 程序清单 10.1
#ifndef STOCK00_H_
#define STOCK00_H_

#include <string>
// 将数据和方法合成一个单元是类最吸引人的特性, 有了这种设计, 在创建对象的时候, 将会自动制定使用对象的规则
class Stock	// Stock 股票  // class declaration
{
private:	// 只能通过公有成员函数(或友元函数)来访问对象的私有成员
			// 将数据放在类的私有部分中称为数据隐藏(防止程序直接访问数据称为数据隐藏), 它亦是一种封装, 将实现的细节隐藏在私有部分中, 就像Stock类对set_tot()所做的那样
			// 封装: 将实现细节放在一起并将它们与抽象分开    // 封装的另一个例子是将类函数的定义和类声明放在不同的文件中
			// 抽象: 类的公共接口的类成员
	std::string company;
	long shares;
	double share_val;
	double total_val;
	void set_tot(){total_val = shares * share_val;}  // 成员函数就地定义
		// 其定义位于类声明中的函数都将自动成为内联函数, 函数应该短小   // 根据改写规则, 在类声明中定义的方法等同于用原型替换方法定义, 然后在类声明的后面将定义改写成为内联函数
		// 也可以在声明函数原型后在实现部分加上inline实现内联函数的转化 inline void Stock::set_tot(){}, 内联函数的特殊规则要求在每个使用它们的文件中都对其进行定义, 确保内联函数定于对多个文件程序中的所有文件都可用的, 最简单的方法是: 将内联函数定义放在定义类的头文件中
public:  // 公有成员函数是程序和对象的私有成员之间的桥梁, 提供了对象和程序之间的接口
	void acquire(const std::string & co, long n, double pr);
	void buy(long num, double price);
	void sell(long num, double price);
	void update(double price);
	void show();  // 成员函数声明, 他们的定义在实现文件中, 对于描述函数接口而言, 原型就足够了
};  // note semicolon at the end

#endif