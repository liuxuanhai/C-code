// 程序清单 3.7
// 浮点数的两种表示方法
#include <stdio.h>
int main (void)
{
	float aboat = 32000.0;
	double abet = 2.14e15;
	long double dip = 5.32e-5;
	printf ("%f can be written %e.\n", aboat, aboat);
	printf ("%f can be written %e.\n", abet, abet);
	printf ("%f can be written %e.\n", dip, dip);
	printf ("%zd", sizeof (int));
	return 0;
}