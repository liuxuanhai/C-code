//printf()和scanf()的*修饰符 4.4.6 (1)
//c primer plus 程序清单 4.16
//varwid.c -- 使用可变参数的输出字段
#include <stdio.h>
int main ()
{
	unsigned width,precision;
	int num = 256;
	double weight = 242.5;

	printf ("What field width?\n");
	scanf ("%d",&width);
	printf ("The number is: %*d: \n", width, num);
	printf ("now enter a width and a precision: \n");
	scanf ("%d %d", &width, &precision);
	printf ("Weight = %*.*f\n", width, precision, weight);
	return 0;
}