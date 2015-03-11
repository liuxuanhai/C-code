#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * argv[])  // 第二个参数是指向char的指针的指针, 不是指向char的指针
{
	FILE * fp;
	char ch;  // EOF是一个负数, char没有负数, 但是作为参数的ch会隐形转换成int所以能执行
	int count = 0;
	
	if (argc != 2)
	{
		printf ("命令行输入错误\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	if (NULL == (fp = fopen(argv[1], "r")))
	{
		puts ("文件不能被打开");
		getchar();
		exit(EXIT_FAILURE);
	}

	while ((ch = getc(fp)) != EOF)
	{
		putc(ch, stdout);
		count++;
	}
	putc('\n', stdout);

	if (fclose(fp) != 0)  // 成功关闭返回0 否则返回-1
		printf ("未能成功关闭文件\n");

	fprintf (stdout, "文件%s一共有%d个字符\n", argv[1], count);
	getchar();

	return 0;
}