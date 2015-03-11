// 编程练习 11.13 (13)
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
	double end = 1;

	if(argc > 2)
	{
		int i = atoi(argv[2]);     // 输入的都是文本格式, 所以不能直接参与运算
		double dou = atof(argv[1]); // 这里也要改
		while (i-- > 0)
			end *= dou;
	}
	else
	{
		puts("输入错误");
		getchar();
		exit(EXIT_FAILURE);
	}
	printf("%lf", end);
	getchar();

	return 0;
}