// 自己总结
// 用一位数组表示二维数组
#include <stdio.h>
void show(int *);
int main(void)
{
	int ar[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0}};
	show(ar[0]);
	return 0;
}
void show(int * ar)
{
	int i = 0;
	for (i = 0; ar[i] != 0; i++)
		printf(" %d \n", ar[i]);
}