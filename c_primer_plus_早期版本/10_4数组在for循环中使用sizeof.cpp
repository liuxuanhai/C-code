// p 247 程序清单10.4 数组的初始化和使用sizeof遍历数组
#include <stdio.h>
int main (void)
{
	const int days[] = {1, 2, 3, 4, 5, 6};

	for (int i = 0; i < sizeof(days) / sizeof days[0]; i++)  // 这里的days是值得整个数组而不是一个地址???
		printf (" %d ", days[i]);

	return 0;
}