// 程序清单 16.18
#include <stdio.h>
#include <stdarg.h> // standard（标准）arguments（参数）
double sum (int, ...);
int main (void)
{
	double s, t;

	s = sum (3, 1.1, 2.5, 13.3); // 3是参数列表中参数的个数
	t = sum (6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1);
	printf ("return value for s is %g\n", s);
	printf ("return value for t is %g\n", t);

	return 0;
}

double sum (int lim, ...)
{
	va_list ap;   // 声明用于存放参数的变量
	va_list apcopy;
	double tot = 0;
	int i;
	va_start (ap, lim); // 把ap初始化为参数列表(把参数列表复制到va_list()参数列表中)
	for (i = 0; i < lim; i++)
		tot += va_arg (ap, double); // 访问参数列表中的每一个项目
						// 第一次调用使用第一个项目第二次使用第二个 可以理解为用一个删一个 想再次访问要用va_copy()??为什么编译器不支持??
	va_end (ap); // 清理工作
	return tot;
}