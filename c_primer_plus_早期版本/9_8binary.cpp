// 递归和反向运算  在反序问题中,递归比循环简单
// c primer plus 程序清单 9.8 p228 
// binary.c -- 以二进制形式输出整数
#include <stdio.h>
void to_binary (unsigned long);      // binary (二进制)

int main (void)
{
	unsigned long number;
	
	printf ("Enter an integer (q to qiut): \n");
	while (scanf ("%ul", &number) == 1)
	{
		printf ("Binary equivalent: ");
		to_binary (number);
		putchar ('\n');
		printf ("Enter an integer (q to qiut): \n");
	}
	printf ("Bye!\n");

	return 0;
}

void to_binary (unsigned long n)    // 递归函数定义
{
	int r;

	r = n % 2;
	if (n >= 2)
		to_binary (n / 2);          // 整数除法 5 / 2结果2.5自动转换为2
	putchar ('0' + r);              // 字符'1'的编码字符'0'的大1;所以putchar()输出1可以写成putchar('0' + 1)
//  putchar (r ? '1' : '0');  也是可以的
	return;                         // return为空是不是就是各级之间不进行return?还是与main?
}