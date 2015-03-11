// p376 编程练习 13.11 (3) 文件复制 转化成大写
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>   // 为toupper()提供原型
#define NAMESIZE 81
#define ARRSIZE 1024

void copy (FILE * dest, FILE * source);

int main (void)
{
	FILE * dest, * source;
	char file_dest[NAMESIZE], file_source[NAMESIZE];
	int i;

	// 目的文件
	puts ("请输入目的文件名:");
	gets (file_dest);
	if (NULL == (dest = fopen (file_dest, "wb")))
	{
		printf ("不能打开目的文件%s.\n", file_dest);
		exit (EXIT_FAILURE);
	}
	else
		puts ("成功打开目的文件!");
	
	// 源文件
	puts ("请输入源文件名:");
	gets (file_source);
	if (NULL == (source = fopen (file_source, "rb")))
	{
		printf ("不能打开源文件文件%s.\n", file_source);
		exit (EXIT_FAILURE);
	}
	else
		puts ("成功打开源文件!");

	// 文件复制 转化成大写
	copy (dest, source);
	
	// 收尾
	fclose (dest);
	fclose (source);
	puts ("复制成功!");

	return 0;
}

void copy (FILE * dest, FILE * source)
{
	char buf[ARRSIZE];
	char temp[ARRSIZE];
	int i;

	while (fgets (buf, ARRSIZE, source) != NULL)
	{
		for (i = 0; i < (int) sizeof (buf) / (int) sizeof (char); i++)
			buf[i] = toupper (buf[i]);
		fputs (buf, dest);
	}
}