// 程序清单 3.3
#include <stdio.h>
int main (void)
{	 
	int x = 100;

	printf ("十进制: %d, 八进制: %o, 十六进制: %x(%X)\n", x, x, x, x);
	printf ("十进制: %d, 八进制: %#o, 十六进制: %#x(%#X)\n", x, x, x, x);

	return 0;
}