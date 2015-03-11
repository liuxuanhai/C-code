			// 类的使用 用户定义类型的使用
// 发送消息: 在OOP中, 调用类成员函数被称作发送消息;

#include <iostream>
#include "研究 - 001类之股票类.h"
int main(void)
{
	std::cout << "--------------------------------------\n";
	{
	// 使用构造函数的方法

			// 显式调用构造函数
	Stock fluffy_the_cat = Stock("显示调用", 250, 1.25);	// C++没有规定这时候是否生成临时对象, 但是本编译器环境下, 不会生成临时变量;

			// 隐式调用构造方法
	{
	Stock YinShi("隐式调用", 50, 2.5);
	}	// 花括号结束, YinShi对象到期, 析构函数被调用

			// 默认构造函数
	Stock Default;
	Default = Stock("生成临时对象赋给Default", 10, 19);		// 构造函数创建一个新的, 临时的对象, 赋值给Default;   
															// 默认情况下, 将一个对象赋值给同类型的另一个对象时, C++将源对象的每个数据成员的内容复制到目标对象中相应的数据成员中;
															// 本编译器下, 临时变量会在执行完赋值操作后立即过期;

			// C++11 列表初始化
	//Stock LieBiao = {"LieBiao", 100, 45.0};	// 本编译器不支持
	//Stock LieBiao1{"LieBiao1", 12, 0.0};		// 本编译器不支持
	//Stock LieBiao2{}; // 调用默认构造函数		// 本编译器不支持


	// fluffy_the_cat.acquire("大雄科技", 20, 12.5); // 不能在创建对象的时候进行初始化, 不如构造函数好用
	fluffy_the_cat.show();
	/*fluffy_the_cat.buy(15, 18.125);
	fluffy_the_cat.sell(400, 20.00);
	fluffy_the_cat.show();
	fluffy_the_cat.buy(3000000, 40.125);
	fluffy_the_cat.show();
	fluffy_the_cat.sell(3000000, 0.125);
	fluffy_the_cat.show();*/

/******************* const成员函数 **************************/
	const Stock ConstObj = Stock("const 对象");
	//ConstObj.buy(0, 0);	// ERROR: 对象包含与成员函数不兼容的类型限定符
							// 此成员函数无法确保调用对象不被修改;
							// 保证它不会修改参数, 在声明函数的时候给参数加上const;
							// 这里保证不修改调用它的对象, 但是对象时隐式调用的, 所以声明的时候应该是 void buy	(long, double) const;
	ConstObj.show();		// 由于void show	(void) const; 声明函数的时候已经表示不会修改对象, 所以这里这样调用时可以的;
/************************************************************/

	Stock YiGeCanShu = "如果类中有接受一个参数的构造函数, 那么这种语法就是可以的";
	YiGeCanShu.show();
	}
	std::cout << "--------------------------------------\n";

	return 0;
}