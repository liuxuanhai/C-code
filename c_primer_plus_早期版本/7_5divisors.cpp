//求一个数的约数
//c primer plus -- 程序清单7.5
//divisors.c -- 使用嵌套循环if显示一个数的约数
#include <stdio.h>
int main (void)
{
	unsigned long num,div;
	int isPrime;  //标志

	printf ("Please enter an integer for analysis:");
	printf ("Enter q to qiut.\n");
	while (scanf ("%lu", &num) == 1)
	{
		for (div = 2,isPrime = 1; div * div <= num; div++)
		{
			if (num % div == 0)
			{
				if (div * div == num)
					printf ("%lu is divisible by %lu\n", num, div);
				else
					printf ("%lu is divisible by %lu and %lu\n", num, div, num / div);
				isPrime = 0;
			}
		}
		if (isPrime)
		{
			printf ("%lu is a prime!\n", num);
		}
		printf ("Please enter an integer for analysis:");
	    printf ("Enter q to qiut.\n");
	}
	return 0;
}