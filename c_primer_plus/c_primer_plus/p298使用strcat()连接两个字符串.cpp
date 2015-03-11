// p298 程序清单 11.14
// strcat(a, b); 用b的内容替换掉第一次遇见'\0'的地方
// string concatenation 他有一个缺点 他并不检查第一个char数组是否能够容纳第二个字符串
#include <stdio.h>
#include <string.h>
#define SIZE 80

int main (void)
{
	char flower[SIZE];
	char addon[] = "s smell like old shoes!";
	puts("Whats your favorite flower?");
	gets(flower);                     // gets()不会读取'\n'
	strcat(flower, addon);
	puts (flower);
	puts (addon);					  // 第二个字符串不变

// 第一个char数组装不下第二个的情况
	char ar1[4];
	char ar2[] = "daxionggege";
	puts(ar2);
	gets(ar1);	// 超过三个字符就会造成内存越界
	strcat(ar1, ar2);
	puts(ar1);    // 必然造成越界
	puts(ar2);

	return 0;
}