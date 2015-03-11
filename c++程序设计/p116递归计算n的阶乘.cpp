// 例5-8 递归计算一个正整数n的阶乘
#include <stdio.h>

long factorial (long); // factorial 阶乘

int main (void)
{
	long n;

	printf ("输入要求阶乘的n值:\n");
	scanf ("%ld", &n);
	printf("结果为:%ld\n", factorial (n));
	
	return 0;
}

long factorial (long n)
{
	if (1 == n)
		return 1;
	else
		return n * factorial (n - 1);
}