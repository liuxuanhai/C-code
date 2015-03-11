// p320 编程练习 13
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[])
{
	int i = 0;
	float num = 1;

	
	if (3 == argc)
 		for (i = 0; i < atoi(argv[argc - 1]); i++)  // 这里不能直接写成argv[2] 因为还没有确定到底会有几个字符串所以只能写成argv[argc - 1]!!!!!!!
			num *= atof (argv[argc - 2]);
	else 
		puts ("输入错误!");
	
	printf ("%0.4f", num);
	scanf ("%d", &i);

	return 0;
}