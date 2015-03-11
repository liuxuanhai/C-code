// p314 程序清单 11.28
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv)
{
	int i, times;

	if (argc < 2 || (times = atoi (argv[2])) < 1)
		puts ("输入错误!");
	else
		for (i = 1; i <= times; i++)
			puts (argv[1]);
	printf("%d", atoi("h")); // . atoi的参数是一个指针, atoi如果转换的不是数字字符指针就会返回0
	scanf ("%d", &i);

	return 0;
}