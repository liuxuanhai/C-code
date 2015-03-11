// p333 程序清单 12.6 (二)
#include <stdio.h>

extern int count;           // 引用声明, 外部链接     extern必须加上, 引用声明必须有   内部链接内部函数使用时不用引用声明
static int total = 0;       // 静态定义, 内部链接
void accumulate (int k);
void accumulate (int k)
{
	static int subtotal = 0;// 静态, 空连接

	if (k <= 0)
	{
		printf ("循环周期:%d.\n", count);
		printf ("subtotal:%d, total:%d.\n", subtotal, total);
		subtotal = 0;
	}
	else
	{
		subtotal += k;
		total +=k;
	}
}