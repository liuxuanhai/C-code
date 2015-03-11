// 指针和数组   指针加法            对一个指针加1的结果是对该指针加1个存储单元
// c primer plus 程序清单 10.8 p254
// pnt_add.c -- 指针加法
#include <stdio.h>
#define SIZE 4
int main (void)
{
	short dates[SIZE];
	short * pti;  // 指针的声明
	short index;
	double bills[SIZE];
	double * ptf;

	pti = dates;  // 把数组的地址赋给了指针
	ptf = bills;
	printf ("%23s %10s\n", "short", "double");     // 指定输出字符串的大小
	for (index = 0; index < SIZE; index++)
		printf ("pointers + %d: %10p %10p\n",
				index, pti + index, ptf + index);

	return 0;
}