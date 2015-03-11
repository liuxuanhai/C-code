// 编程练习 10.10 (4) 客户文件
#include <iostream>
#include "p378编程练习4.h"

int main()
{
	using SALES::Sales;  // 声明名称空间中的Sales类

	double vals[3] = {2000, 3000, 5000};
	Sales forFiji(vals, 3);
	forFiji.showSales();

	Sales red;
	red.showSales();
	red.setSales();
	red.showSales();

	return 0;
}