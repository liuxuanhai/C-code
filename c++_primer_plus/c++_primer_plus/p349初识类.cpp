// 程序清单 10.3
// 类的使用       类就是用户定义的类型!!!!!!!!!!
#include <iostream>
#include "p343初识类.h"
int main()
{
	Stock fluffy_the_cat;  // 所创建的每个对象都有自己的存储空间, 用于存储其内部变量和类成员; 但是同一个类的所有对象共享同一组类方法, 即每种方法只有一个副本
						  // 在oop中, 调用成员函数被称为发送消息, 因此将同样的消息发送给两个不同的对象将调用同一个方法, 但是发方法被用于两个不同的对象
		// 如果没有提供任何的构造函数, 则c++自动提供默认的构造函数, 他是默认构造函数的隐式版本, 不做任何工作, 对于stock类来说默认的构造函数可能如下:Stock::Stock(){}

	fluffy_the_cat.acquire("NanoSmart", 20, 12.5);
	fluffy_the_cat.show();
	fluffy_the_cat.buy(15, 18.125);
	fluffy_the_cat.show();
	fluffy_the_cat.sell(400, 20.00);
	fluffy_the_cat.show();
	fluffy_the_cat.buy(300000, 40.125);
	fluffy_the_cat.show();
	fluffy_the_cat.sell(300000, 0.125);
	fluffy_the_cat.show();

	return 0;
}