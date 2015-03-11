// 抛N次硬币, 实验M次
#include <stdio.h>
#include <stdlib.h>

int heads()
{
	return rand() < RAND_MAX/2;
}

int main(void)
{
	int i, j, cnt;
	int N, M;
	
	printf("抛硬币次数: ");
	scanf("%d", &N);
	printf("实验次数: ");
	scanf("%d", &M);
	
		// 为抛硬币的次数分配内存空间  ID: 0 - N分别表示抛N次硬币, 正面朝上ID次, 对应保存的值是ID次在执行M次情况下对应的次数
	int *f = (int *)malloc((N+1) * sizeof(int));

		// 将初始值赋值为0
	for (j = 0; j <= N; j++)
		f[j] = 0;

		// 抛N次, 执行M遍
	for (i = 0; i < M; i++)	// M遍
	{
			// 统计正面朝上的次数
		for (cnt = 0, j = 0; j <= N; j++)	// N次
			if (heads())	// 如果正面朝上
				cnt++;

			// 将正面朝上的次数相对应的数组ID加一
		f[cnt]++;
	}

		// 输出
	for (j = 0; j <= N; j++)
	{
		printf("%2d", j);
		for (i = 0; i < f[j]; i += 10)
			printf("*");
		printf("\n");
	}

	return 0;
}