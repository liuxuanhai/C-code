// 程序清单 16.18
#include <stdio.h>
#include <stdarg.h>  // standard argument
double sum(int, ...);
int main(void)
{
	double s, t;

	s = sum(3, 1.1, 2.5, 13.3);  // 3 is argument list's arguments
	printf("return value for s is %g\n", s);
	//t = sum(6, 1, 2, 3, 4, 5, 6);  对于这个用宏操作的东西, 没有自动的类型转换, 不能将int转化为double
	t = sum (6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1);
	printf ("return value for t is %g\n", t);

	return 0;
}

double sum(int lim, ...)
{
	va_list ap;  // 声明用于存放参数的变量
	va_list apcopy;  // 保存的副本
	double tot = 0;
	int i;
	va_start(ap, lim);  // 把ap初始化为参数列表(把参数列表复制到va_list()参数列表中)
	va_start(apcopy, lim);
	for (i = 0; i < lim; i++)
		tot += va_arg(ap, double);  // 访问参数列表中的每个项目
				// 第一次调用使用第一个项目, 第二次调用使用第二个, 可以理解为用一个删一个
	printf("--%f--", va_arg(apcopy, double));
	va_end(ap);  // 清理工作 eg: 释放动态分配的用于存放参数的动态内存
	va_end(apcopy);
	return tot;
}