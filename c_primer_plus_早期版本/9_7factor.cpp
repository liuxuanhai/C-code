// 用循环和recur(递归)计算阶乘
// c primer plus 程序清单 9.7 p226
// factor.c -- 使用循环和递归计算阶乘
#include <stdio.h>
long fact (int n);
long rfact (int n);
int main (void)
{
	int num;

	printf ("This program calculates(计算) factorials(阶乘).\n");
	printf ("Enter a value in the range 0-12 (q to qiut):\n");
	while (scanf ("%d", &num) ==1)
	{
		if (num < 0)
			printf ("No negative numbers(负数), please.\n");
		else if (num > 12)
			printf ("Keep input under 13.\n");
		else 
		{
			printf ("loop(循环): %d factorial = %ld\n", num, fact(num));
			printf ("recursion: %d factorial = %ld\n", num, rfact(num));
		}
		printf ("Enter a value in the range 0-12 (q to quit):\n");
	}
	printf ("Bye!\n");
	return 0;
}

long fact (int n)
{
	long ans;

	for (ans = 1; n > 1; n--)
		ans *= n;
	
	return ans;
}

long rfact (int n)              // 递归里面的变量是互不影响的他们各自独有一个内存地址
{
	long ans;

	if (n > 0)
		ans = n * rfact (n-1);  // 把递归调用语句放在函数结尾即恰好在return之前成为尾递归 这条语句是在n>0时执行的最后一条 所以也算是尾递归
	else 
		ans = 1;                

	return ans;
}

