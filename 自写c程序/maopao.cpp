// 检测自定义冒泡函数对变量值交换的作用范围
#include <stdio.h>
int maopao (int a, int b);
int main (void)
{
	int n1,n2;

	scanf ("%d %d", &n1, &n2);
	maopao (n1, n2);
	printf ("n1 -> %d   n2 -> %d\n", n1,n2);
	return 0;
}
int maopao (int a, int b)  // 调用自定义函数时给形式变量传的是数值,所以他对调用时赋给他的参数没有任何影响~~~
{
	int temp;

	if (a > b)
	{
		temp = a;
		a = b;
		b = temp;
		printf ("n1:%d.n2:%d\n", a, b);
	}
	return b;
}