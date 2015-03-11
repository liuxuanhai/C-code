			// 类的使用 用户定义类型的使用
// 发送消息: 在OOP中, 调用类成员函数被称作发送消息;

#include <iostream>
#include "p343 初始类.h"
int main(void)
{
	Stock fluffy_the_cat;

	fluffy_the_cat.acquire("大雄科技", 20, 12.5);
	fluffy_the_cat.show();
	fluffy_the_cat.buy(15, 18.125);
	fluffy_the_cat.sell(400, 20.00);
	fluffy_the_cat.show();
	fluffy_the_cat.buy(3000000, 40.125);
	fluffy_the_cat.show();
	fluffy_the_cat.sell(3000000, 0.125);
	fluffy_the_cat.show();

	return 0;
}