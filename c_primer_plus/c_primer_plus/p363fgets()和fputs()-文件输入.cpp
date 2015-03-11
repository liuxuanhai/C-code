// p363 程序清单 13.4 -- 文件输入
#include <stdio.h>
#define MAXLINE 4
int main (void)
{
	char line[MAXLINE];
	FILE * fp;
	fp = fopen ("words.txt", "r");
	while (fgets (line, MAXLINE, fp) != NULL)   // MAXLINE表示输入字符串的最大长度
	{
		puts("...");
		fputs (line, stdout);
		printf ("-%c-%c-%c-", line[0], line[1], line[2]);  // 看起来是一个回车产生了两个空行, 其实是当地一个为回车的时候自动清空缓冲, 所以line[1]为'\0'
		putchar ('\n');
		puts("...");
	}
	return 0;
}
// fgets() 读取到他所遇到的第一个换行字符的后面, 或者读取比字符串最大长度少一个的字符, 或者读到文件结尾.
// 然后fgets()向末尾添加一个空字符以构成一个字符串.