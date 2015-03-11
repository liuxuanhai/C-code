// c primer plus 程序清单 9.10 p232
// hotel.c -- 旅馆管理函数
// 跟9.9控制模块相关联
#include <stdio.h>
#include "9__11hotel.h"
int menu (void)
{
	int code, status;

	printf ("\n%s%s\n", STARTS, STARTS);
	printf ("Enter the number of the desired hotel: \n");
	printf ("1. Fairfield Arms  2. Hotel Olympic\n");
	printf ("3.Chertwothy Plaza  4. The Stockton\n");
	printf ("5. qiut\n");
	printf ("\n%s%s\n", STARTS, STARTS);
	// 对用户错误输入的处理
	while ((status = scanf ("%d", &code)) != 1 ||    // 输入是不是非int的判断   // 用到了两个原则: 1. 逻辑表达式从左向右运算. 2. 只有确定了scanf()已经成功读入了才进行code的检查
		           (code < 1 || code > 5))           // int是不是1-5的判断
	{
		if (status != 1)
			scanf ("%*s");                           // 如果是非int那么将不会读入, 会影响下次读入, 所以用这个来跳至下一个空白字符
		printf ("Enter an integer from 1 to 5, please.\n");
	}
	
	return code;
}

int getnights (void)
{
	int nights;

	printf ("How many nights are needed? ");
	// 判断用户的输入是否符合规则
	while (scanf ("%d", &nights) != 1)
	{
		scanf ("%*s");
		printf ("Please enter an integer, such as 2.\n");
	}
	return nights;
}

void showprice (double rate, int nights)
{
	int n;
	double total = 0.0;
	double factor = 1.0;

	for (n = 1; n <= nights; n++,factor *= DISCOUNT)
		total += rate * factor;
	printf ("The total cost will be $%0.2f.\n", total);
}