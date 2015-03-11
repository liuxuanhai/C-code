//c primer plus 程序清单 4.7 使用修饰符和标志示例(2)
//floats.c -- 一些浮点数的组合
#include <stdio.h>

int main ()
{
	const double RENT = 3852.99;  //以const方法定义的常量

	printf ("*%f*\n",RENT);
	printf ("*%e*\n",RENT);
	printf ("*%4.2f*\n",RENT);
	printf ("*%3.1f*\n",RENT);
	printf ("*%10.3f*\n",RENT);
	printf ("*%10.3e*\n",RENT);
	printf ("*%+4.2f*\n",RENT);
	printf ("*%010.2f*\n",RENT);
	return 0;
}