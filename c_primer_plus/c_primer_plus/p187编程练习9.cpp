// 编程练习 7.14 (9)
// 接受一个整数, 显示小于这个整数的所有素数
// 2是最小的素数, 也是唯一的偶素数
#include <stdio.h>
int main(void)
{
	int max;
	int j;

	puts("请输入一个数, 我会给你所有小于或等于输入值的素数.");
	scanf("%d", &max);
	for(int i = 2; i <= max; i++)
	{	
		for(j = 2; j * j <= i; j++)
		{
			if(i % j == 0)
				break;
		}
		if(j * j > i)
			printf("%d ", i);
	}

	return 0;
}