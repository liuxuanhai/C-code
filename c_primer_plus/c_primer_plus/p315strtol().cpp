// 程序清单 11.29
// long strtol(const char * nptr, char ** endptr, int bse); nptr是指向希望转换的字符串的指针 endptr是指向标志输入数字的结束字符的指针的地址, base是数字的基数(最多36进制使用一直到'z'作为数字)
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char number[30];
	char * end;
	long value;

	puts("Enter a number (empty line to quit):\n");
	while (gets(number) && number[0] != '\0')
	{
		value = strtol(number, &end, 10);
		printf("value: %ld, stopped at %s (%d)\n", value, end, *end); // 如果输入的是"12\0"那么end就是最后'\0'的地址, end(%s)输出的话此字符串为空, 什么都不输出, *end(%d)输出的话只能输出0
		value = strtol(number, &end, 16);
		printf("value: %ld, stopped at %s (%d)\n", value, end, *end);
		value = strtol(number, &end, 8);
		printf("value: %ld, stopped at %s (%d)\n", value, end, *end);
	}

	return 0;
}