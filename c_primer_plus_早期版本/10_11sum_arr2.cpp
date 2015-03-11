// 函数,数组和指针    定义形式参量为数组的函数的声明
// c primer plus 程序清单 10.11 p258
// sum_arr2.c -- 对一个数组的所有元素求和
#include <stdio.h>
#define SIZE 10
int sum (int * start, int * end);     // int ar[]==int*ar -- ar是指向int的指针
int main (void)
{
	int marbles[SIZE] = {20, 10, 5, 39, 4, 16, 19, 26, 31, 20};
	long answer;

	answer = sum (marbles, marbles + SIZE);
	printf ("The total number of marbles is %ld.\n", answer);
	printf ("The size of marbles is %u bytes.\n", sizeof marbles);  // marbles有10字节,因为marbles包含10个int类型的数,每个数占四个字节

	return 0;
}

int sum (int * start, int * end) // 使用指针参量来确定数组的开始点,使用另一个参量指明数组的元素个数,还有另一方法程序清单10.11
{
	int total = 0;

	while (start < end)
	{
		total += *start;
		start++;
	}
	
	return total;
}