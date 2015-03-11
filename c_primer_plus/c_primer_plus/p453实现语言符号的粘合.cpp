// 程序清单 16.4 ## 实现语言符号的粘合
#include <stdio.h>
#define XNAME(n) x ## n
#define YNAME x3
#define PRINT_XN(n) printf ("x" #n " = %d\n", x ## n);

int main (void)
{
	int XNAME(1) = 14; // 变为int x1 = 14;
	int XNAME(2) = 20; // 变为int x2 = 20;
	int YNAME = 10;
	PRINT_XN(1);       // 变为printf ("x1 = % d \n", x1);
	PRINT_XN(2);       // 变为printf ("x2 = % d \n", x2);
	printf("%d", x3);
	return 0;
}