// 复习题 13.10 计算输入double的平均值
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	FILE * fp;
	int count = 0;
	double dou;
	double tot = 0, avg = 0;

	if (argc == 2)
	{
		if (NULL == (fp = fopen(argv[1], "r")))
		{
			fprintf(stderr, "无法打开%s文件\n", argv[1]);
			getchar();
			exit(EXIT_FAILURE);
		}
		while (fscanf(fp, "%lf", &dou) == 1)
		{
			tot += dou;
			count++;
		}
	}
	else if (argc == 1)
		while (scanf("%lf", &dou) == 1)
		{
			tot += dou;
			count++;
		}
	else
	{
		fprintf(stderr, "命令行参数不正确.\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	avg = tot / count;
	printf("一共输入了%d个double数字, 总和为%lf, 平均数为%lf\n", count, tot, avg);
	getchar();

	return 0;
}