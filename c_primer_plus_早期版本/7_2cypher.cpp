//getchar()和putchar()
//c primer plus 程序清单 7.2
//cypher.c -- 改变输入,只保留其中的空格
#include <stdio.h>
#define SPACE ' '
int main (void)
{
	char ch;

	while ((ch = getchar()) != '\n')
	{
		if (ch == SPACE)
			putchar (ch);
		else
			putchar(ch + 1);
	}
	putchar (ch);
	return 0;
}