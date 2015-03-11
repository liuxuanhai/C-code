// 编程练习 7.14 (9) 标准答案
#include <stdio.h>
#define YES 1
#define NO 0
int main(void)
{
	long num;
	long div;
	long lim;
	int prime;

	puts("请输入一个数, 我会给你所有小于或等于输入值的素数.");
	while(1 == scanf("%ld", &lim) && lim > 0)
	{
		for(num = 2; num <= lim; num++)
		{
			for(div = 2, prime = YES; (div * div) <= num; div++)
				if(num % div == 0)
					prime = NO;
			if(prime == YES)
				printf("%ld ", num);
		}
		puts("请输入一个数, 我会给你所有小于或等于输入值的素数.");
	}

	return 0;
}