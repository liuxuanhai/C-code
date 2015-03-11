// 递归: 函数调用其本身的过程被称作递归  递归没有循环效率高
// c primer plus 程序清单 9.6 p225
// recur.c -- 递归举例     recur 重现 
#include <stdio.h>
void up_and_down (int);

int main (void)
{
	up_and_down (1);
	return 0;
}

void up_and_down (int n)
{
	printf ("Level %d: n location %p\n", n, &n);  // 1
	if (n < 4)
		up_and_down (n+1);
	printf ("LEVEL %d: n location %p\n", n, &n);  // 2

}