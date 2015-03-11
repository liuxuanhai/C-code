// p356 程序清单 13.1
#include <stdio.h>
#include <stdlib.h>     // exit ();的原型

int main (int argc, char * argv[])
{
	int ch;            // 读取时储存每个字符的位置
	FILE * fp;         // 文件指针
	long count = 0;

	if (argc != 2)
	{
		printf ("未能给%s成功指定文件!\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ((fp = fopen (argv[1], "r")) == NULL)
	{
		printf ("不能打开%s!", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((ch = getc (fp)) != EOF)
	{
		putc (ch, stdout);       // 相当于putchar(ch);
		count++;
	}
	fclose (fp);
	printf ("文件%s有%d个字符.\n", argv[1], count);
	scanf ("%d", &count);
	
	return 0;
}