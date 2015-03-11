//检查用户的输入除了单双引号和句号外公多少个字符
//c primer plus 程序清单 7.6
//chcount.c -- 使用逻辑运算符
#include <stdio.h>
#define PERIOD '.'
int main (void)
{
	char ch;
	int charcount = 0;

	printf ("请输入几个字符:\n");
	while ((ch = getchar()) != '.')
	{
		if (ch != '"' && ch != '\'')
			charcount++;	
	}
	printf ("There are %d non-quote characters.\n", charcount);
	return 0;
}