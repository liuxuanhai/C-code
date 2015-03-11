// 混合输入数字和字符 输入一个字符两个数字 字符按数字为行列打印他
// c primer plus 程序清单 8.5 p198
// showchar.c -- 带有一个较大的I/O问题的程序
#include <stdio.h>
void display (char cr, int lines, int width);
int main (void)
{
	int ch;
	int rows, cols;

	printf ("Enter a character and two integers: \n");
	while ((ch = getchar()) != '\n')
	{
		scanf ("%d %d", &rows, &cols);
		display (ch, rows, cols);
		while (getchar() != '\n')      // 剔除scanf()输入后的所有字符,包括换行符,getchar读入换行符(屏蔽后输入c 2 3响应后直接退出不能继续输入)
			continue;
		printf ("Enter another character and two integers: \n");
		printf ("Enter a new line to quit.\n");
	}
	printf ("Bye.\n");
	return 0;
}
void display (char cr, int lines, int width)
{
	int row, col;

	for (row = 1; row <= lines; row++)
	{
		for (col = 1; col <= width; col++)
			putchar (cr);
		putchar ('\n');               // 结束本行 开始新的一行
	}
}