// p363 程序清单 13.4 -- 键盘输入
#include <stdio.h>
#define MAXLINE 20
int main (void)
{
	char line[MAXLINE];
	
	while (fgets (line, MAXLINE, stdin) != NULL   // MAXLINE表示输入字符串的最大长度
			&& line[0] != '\n')
		fputs (line, stdout);
	return 0;
}
// fgets() 读取到他所遇到的第一个换行字符的后面, 或者读取比字符串最大长度少一个的字符, 或者读到文件结尾.
// 然后fgets()向末尾添加一个空字符以构成一个字符串.