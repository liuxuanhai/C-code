// 程序清单 10.9 实现文件
#include <iostream>
#include "p365this指针.h"

const int STKS = 4;
int main()
{
// create an array of initialized object
	Stock stocks[STKS] = {
		Stock("NanoSmart", 12, 20.0),
		Stock("Boff Objects", 200, 2.0),
		Stock("Monolithic Obelisks", 130, 3.25),
		Stock("Fleep Enterprises", 60, 6.5)
	};	// 初始化对象数组的方案是: 首先使用默认构造函数创建数组元素, 然后花括号中的构造函数将创建临时对象, 然后临时对象的内容复制到相应的元素中, 因此, 要创建对象数组, 这个类必须有默认构造函数
	std::cout << "Stock holdings:\n";
	int st;
	for (st = 0; st < STKS; st++)
		stocks[st].show();

// set pointer to first element
	const Stock * top = &stocks[0];
	for (st = 1; st < STKS; st++)
		top = &top->topval(stocks[st]);

// now top points to the most valuable holding
	std::cout << "\nMost valuable holding:\n";
	top->show();
	return 0;

	return 0;
}