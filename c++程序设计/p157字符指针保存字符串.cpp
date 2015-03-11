// p157 字符指针 字符指针保存字符串
#include <stdio.h>
int main (void)
{
	char * s = "string1";
	printf ("%s\n", s);
	
	s = "string2";      // 将字符串的首地址赋予指针上
	printf ("%s\n", s);
	
	return 0;
}