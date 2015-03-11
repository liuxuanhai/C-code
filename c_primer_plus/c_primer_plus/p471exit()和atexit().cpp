// 程序清单 16.14
// atexit(); 使用指针参数
#include <stdio.h>
#include <stdlib.h>
void sign_off (void);
void too_bad (void);

int main (void)
{
	int n;

	atexit (sign_off);     // 注册sign_off();函数 // 函数名代表地址
	puts ("Enter an integer: ");
	if (1 != scanf ("%d", &n))
	{
		puts ("That's not an integer!");
		atexit (too_bad);
		exit (EXIT_FAILURE); // 调用exit()的时候按"先进后出"的原则对注册函数进行调用 注: main()结束的时候会隐式的调用exit()所以即使输入的是integer也会输出sign_off
	}
	printf ("%d is %s.\n", n, (n % 2 == 0) ? "even" : "odd");

	return 0;
}

void sign_off (void)
{
	puts ("sign_off");
}

void too_bad (void)
{
	puts ("too_bad");
}