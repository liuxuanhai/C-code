// 标准答案  // 使用标准输入的时候只需要fp = stdin;即可
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	FILE * fp;
	double n;
	double sum = 0.0;
	int ct = 0;

	if (argc == 1)  // 如果没有使用命令行的话, 输入fp文件指针指向的是标准输入文件
		fp = stdin;
	else if (argc == 2)
	{
		if (NULL == (fp = fopen(argv[1], "r")))
		{
			fprintf(stderr, "Can't open %s\n", argv[1]);
			getchar();
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		getchar();
		exit(EXIT_FAILURE);
	}
	while (fscanf(fp, "%lf", &n) == 1)
	{
		sum += n;
		++ct;
	}
	if (ct > 0)
		printf("Average of %d values = %f\n", ct, sum / ct);
	else
		printf("No valid data.\n");

	getchar();

	return 0;
}