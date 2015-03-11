//如何判断输入字符时字母还是非字母
//c primer plus 程序清单 7.3
//cypher1.c -- 改变输入,只保留字母字符
#include <stdio.h>
#include <ctype.h>
int main (void)
{
	char ch;

	while((ch = getchar()) != '\n')
	{
		if (isalpha(ch))
			putchar (ch + 1);
		else
			putchar (ch);
	}
	putchar (ch);
	return 0;
}