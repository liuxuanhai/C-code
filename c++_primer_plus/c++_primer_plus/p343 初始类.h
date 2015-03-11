// 将数据和方法合成一个单元是类最吸引人的特性, 有了这种设计, 在创建对象的时候, 将会自动定制使用对象的规则;

#ifndef p343初始类_H_
#define p343初始类_H_

#include <string>

	// 类声明 - 一个保存用户对某公司持有股票的类;

class Stock
{
		// 只能用公有成员函数和友元函数访问private成员(默认访问方式);
		// 将数据放在类的私有部分称为数据隐藏, 它防止了程序直接访问数据成员, 这亦是一种封装, 将实现的细节封装在私有部分中;
private:
			// 这里只是声明了这些数据, 并没有赋值, 所以没有定义, 也没有分配空间, 所以可以放在头文件中, 文件的外部全局变量多次声明木有问题, 多次定义就不行了;
	std::string company;
	long		shares;		// 股份
	double		share_val;	// 股价
	double		total_val;	// 总持有价值
	
		// 定义位于类声明中的函数都将会自动成为内联函数, 不然放在头文件中也不允许;
	void set_tot(void){total_val = shares * share_val;}  // 内联函数是通过将函数限制成内部链接实现的可以放在头文件

		// 公有函数提供了对象和程序之间的接口;
public:
	void acquire(const std::string &, long, double);  // acquire额快儿: 获取
	void buy	(long, double);
	void sell	(long, double);
	void update	(double);
	void show	(void);
};

#endif