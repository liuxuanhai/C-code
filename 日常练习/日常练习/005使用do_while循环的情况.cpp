// 对比while和do while 找到适合do while的情况
#include <stdio.h>
int main(void)
{
	int i, j;

	j = scanf("%d", &i);
	while(1 == j)
	{
		printf("%d\n", i);
		j = scanf("%d", &i);
	}
	getchar();
	puts("---------");

	do
	{
		j = scanf("%d", &i);
		printf("%d\n", i);
	}while (1 == j);

	return 0;
}