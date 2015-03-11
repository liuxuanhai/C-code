// EOF终止键盘输入
// C primer plus 程序清单 8.2 p191
// echo_eof.c -- 重复输入,直到文件结尾
#include <stdio.h>
int main (void)
{
	int ch;     // 文件的结尾为EOF 而EOF的值有可能为-1 这对char(0-255)是不可能的 // 但是定义为char也行 但是不是最好的形式

	printf ("在本pc上,只有在每行的开始输入Ctrl+z会被认为是文件结尾.\n");
	while ((ch = getchar()) != EOF)
		putchar(ch);
	return 0;
}