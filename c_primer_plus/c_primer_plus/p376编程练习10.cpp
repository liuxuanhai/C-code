// 编程练习 13.11 用户输入一个文件位置, 打印出此位置到下一个换行符
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE * fp;
	char filename[81];
	long pos, last;

	puts("File name: ");
	gets(filename);
	if (NULL == (fp = fopen(filename, "rb")))
	{
		fprintf(stderr, "Can't open %s.\n", filename);
		exit(EXIT_FAILURE);
	}

	puts("输入一个文件位置(非数字退出):");
	while (scanf("%ld", &pos) == 1)
	{
		fseek(fp, 0L, SEEK_END);
		last = ftell(fp);
		if (pos >= last)
		{	
			fprintf( stderr, "输入的数字大于%d, 重新输入:\n", last);
			continue;
		}
		fseek(fp, pos, SEEK_SET);
		fgets(filename, 81, fp);
		fputs(filename, stdout);
		puts("输入一个文件位置(非数字退出):");
	}

	puts("Done!");

	return 0;
}