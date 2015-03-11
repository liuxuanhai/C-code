// c primer plus 程序清单 8.3 p195
// file_eof.c -- 打开一个文件并显示其内容
#include <stdio.h>
#include <stdlib.h>                          // 为了使用exit()
int main (void)
{
	int ch;                                  // 为了使用EOF定义为int
	FILE * fp;
	char fname[50];                          // 用于存放文件名

	printf ("Enter the name of the file:\n");
	scanf ("%s", fname);                     // 这里的fname没有加&符号
	fp = fopen (fname, "r");                 // 打开文件以供读取
	if (fp == NULL)                          // 尝试打开文件失败
	{
		printf ("Failed to open the file. Bye!\n");
		exit (1);                            // 终止程序
	}
	// getc (fp) 从打开的文件中获取一个字符
	while ((ch = getc (fp)) != EOF)
		putchar (ch);
	printf ("\n");
	fclose (fp);                             //关闭文件
	return 0;
}