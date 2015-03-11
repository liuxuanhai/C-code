// p376 编程练习 13.11 (8)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_file (char ch, FILE * file);
int find_std (char ch);

int main (int argc, char * argv[])
{
	FILE * file;
	char ch;
	int i;

	// 未输入文件名
	if (argc < 3)
	{   // 字符
		puts ("请输入要查找的字符:");
		scanf ("%c", &ch);
		printf ("std ->>%c->> %d.\n", ch, find_std (ch));
	}
	// 输入了文件名
	else
		for (i = 2; i < argc; i++)
		{
			if (NULL == (file = fopen (argv[i], "r")))
			{
				printf ("不能打开文件%s!\n", argv[i]);
				exit (EXIT_FAILURE);
			}
			printf ("%s ->>%c->> %d.\n", argv[i], argv[1][0], find_file (argv[1][0], file));
			fclose (file);
		}
	system ("pause");
	puts ("ok!");

	return 0;
}

int find_std (char ch)
{
	int count = 0;
	char t_ch;

	puts ("请输入要进行查找的文本('|'结束):");
	while ((t_ch = getchar()) != '|')
	{	
		if (t_ch == ch)
			count++;
	}
	return count;
}

int find_file (char ch, FILE * file)
{
	int count = 0;
	char t_ch;

	while ((t_ch = getc (file)) != EOF)
	{	
		if(t_ch == ch)
			count++;
	}

	return count;
}