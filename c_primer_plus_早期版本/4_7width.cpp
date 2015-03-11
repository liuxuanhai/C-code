//c primer plus 程序清单 4.7 使用修饰符和标志示例(1)
//width.c -- 字段宽度
#include <stdio.h>
#define PAGES 931
int main ()
{
	printf ("*%d*\n",PAGES);
	printf ("*%2d*\n",PAGES);
	printf ("*%10d*\n",PAGES);
	printf ("*%-10d*\n",PAGES);
	return 0;
}
