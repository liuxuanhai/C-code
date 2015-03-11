#include <stdio.h>

int main(void)
{
	// 取反~
	unsigned char a = 2;
	printf ("%d\n", ~a);  // 一个数为2 如果想取到-2 那么只需取反加1  这里证明系统默认类型为有符号
	unsigned char aa = ~a;
	printf ("%d\n", aa);  // 如果定义的aa是无符号的话那么就会取到253

	// 与 掩码
	unsigned int b = 65535;
	printf("%d\n", b);
	b &= 255;//0377;//0xff;
	printf("%d\n", b);

	// 移位运算符
	int num = 1;
	printf("%d\n", num);
	num <<= 2;
	printf("%d\n", num);
	int n = 4;
	printf("%d\n", n);
	n >>= 2;
	printf("%d\n", n);  // 对于有符号的补零还是补1取决于系统 对于无符号的都是补零

	return 0;
}