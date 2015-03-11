//输入 -> 感叹号替代句号,双感叹号替代感叹号 -> 报告进行了多少次替换
//c primer plus 编程练习 p187 4
#include <stdio.h>
int main ()
{
	char ch;
	int num = 0;

	printf ("请输入要进行替换的字符串(#结束程序):\n");
	while ((ch = getchar()) != '#')
	{
		if ('!' == ch)
		{
			printf ("!");
			num++;
		}
		if ('.' == ch)
		{
			ch = '!';
			num++;
		}
		putchar (ch);	
	}
	printf ("一共进行了%d次替换\n", num);
	return 0;
}