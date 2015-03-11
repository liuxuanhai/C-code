// 程序清单 16.4 #和##
#include <stdio.h>
#define XNAME(n) bianliang ## n  // 用于变量名的粘合剂 书写成一个变量名
#define PRINT_XN(n) printf("bianliang" #n " = %d\n", bianliang ## n);  // #用作一个预处理运算符, 可以把语言符号转化成字符串 ##把两个语言符号组合成一个语言符号
								// #n 把参数转化成相应的字符串
int main(void)
{
	int XNAME(1) = 14;  // change to bianlinag1 = 14
	int XNAME(2) = 20;  // change to bianliang2 = 20
	PRINT_XN(1);  // change to printf("bianliang1 = %d\n", bianliang1);
	PRINT_XN(2);  // change to printf("bianliang2 = %d\n", bianliang2);
		// #2转化成了"2" printf("bianliang""2"" = %d\n", bianliang2);
	int temp = bianliang1 + bianliang2;
	printf("%d\n", temp);

	return 0;
}