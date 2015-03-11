// 反向打印一个字符串
#include <stdio.h>
#include <string.h>
#define SIZE 100
int main(void)
{
	char ar[SIZE];

	puts("给我一个字符串我给你反向打印出来:");
	gets(ar);
	for(int i = strlen(ar) - 1; i >= 0; i--)
	{
		putchar(ar[i]);
	}
	putchar('\n');

	return 0;
}