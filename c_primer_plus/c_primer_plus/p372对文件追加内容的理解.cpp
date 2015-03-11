// 自己写的加深p371程序的理解
#include <stdio.h>
#include <stdlib.h>          // 为exit()提供函数原型
#include <string.h>          // 为strcmp()提供函数原型
#define FNAME 81

void append (FILE * source, FILE * dest);

int main (void)
{
	FILE * fa, * fs;
	char file_app[FNAME], file_src[FNAME];

	// 目标文件
	puts ("请输入目标文件名:");
	gets (file_app);
	if (NULL == (fa = fopen (file_app, "a")))
	{
		printf ("不能打开目标文件%s!\n", file_app);
		exit (EXIT_FAILURE);
	}
	else
		printf ("成功打开%s!\n", file_app);

	// 源文件
	puts ("请输入源文件(空行退出):");
	while (gets (file_src) && file_src[0] != '\0')  // gets() 读取'\n'以后替换成'\0' 所以不写成'\n'
	{
		if (strcmp (file_app, file_src) == 0)
		{	
			puts ("不能对目标文件自己进行追加操作!请重新输入!");
			continue;
		}
		else if (NULL == (fs = fopen (file_src, "r")))
		{
			puts ("不能打开此源文件!请重新输入");
			continue;
		}
		else
		{
			append (fa, fs);
			fclose (fs);
			puts ("已经成功对目标文件进行了追加!\n请输入下一个源文件(空行退出):");
		}
	}

	// 结尾
	fclose (fa);
	puts ("ok!");

	return 0;
}

void append (FILE * dest, FILE * source)
{
	char str[4];

	while (fgets (str, 4, source) != NULL)
	{
		fputs (str, dest);
	}
}