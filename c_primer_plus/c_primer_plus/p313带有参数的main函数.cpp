// p313 程序清单 11.27 带有参数的main函数
#include <stdio.h>

int main (int argc, char * argv[])
{
	int count;

	printf ("命令行有%d个参数.\n", argc - 1);
	printf("argc = %d", argc);
	for (count = 0; count < argc; count++)
		printf ("argv[%d]->%s\n", count, argv[count]);
	printf ("\n");
	scanf ("%d", &count);

	return 0;
}