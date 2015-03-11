// 数组的初始化            // 不能成功运行!!!!!!!!!!!!!!!!!!!!
// c primer plus 程序清单 10.5 p248
// designnate.c -- 使用指定初始化项目    designate 指定
#include <stdio.h>
#define MONTHS 12
int main (void)
{
	int days[MONTHS] = {31, 28, [4] = 31, 30, 31, [1] = 29};
	int i;
	for (i = 0; i < MONTHS; i++)
		printf ("%2d月 [%d] %d", i + 1, i, days[i]);
	
	return 0;
}