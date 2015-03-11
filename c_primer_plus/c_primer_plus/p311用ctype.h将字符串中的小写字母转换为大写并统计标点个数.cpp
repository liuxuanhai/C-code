// p311 程序清单 11.26
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LIMT 80

void ToUpper (char *);           // 将小写字母转化为大写
int punctcount (const char *);   // 统计字符串中标点符号的个数

int main (void)
{
	char line[LIMT];

	puts ("输入一个字符串,我帮你把小写变大写并告诉你标点符号的个数:");
	gets (line);
	ToUpper (line);
	puts (line);
	printf ("有%d个标点符号!\n", punctcount(line));

	return 0;
}

void ToUpper (char * str)
{
	while (*str)
	{
		*str = toupper (*str);     // 前面的*str = 必须加上!!!!!!!!!!!!
		str++;
	}

	return;
}

int punctcount (const char * str)
{
	int count = 0;
	while (*str)
	{
		if (ispunct (*str))
			count++;
		*str++;
	}
		
	return count;
}