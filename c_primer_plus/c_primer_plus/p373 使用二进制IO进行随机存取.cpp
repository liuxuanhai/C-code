#include <stdio.h>
#include <stdlib.h>
#define ARSIZE 1000

int main(void)
{
	double numbers[ARSIZE];
	double value;
	const char * file = "p373numbers.dat";
	int i;
	long pos;
	FILE * infile;

	for (i = 0; i < ARSIZE; i++)
		numbers[i] = 100.0 * i + 1.0 / (i + 1);
	
	if (NULL == (infile = fopen(file, "wb")))
	{
		fprintf(stderr, "不能打开%s文件.\n", file);
		exit(EXIT_FAILURE);
	}

	// 把数组中的数据以二进制形式写入文件
	fwrite(numbers, sizeof(double), ARSIZE, infile);
	fclose(infile);

	if (NULL == (infile = fopen(file, "rb")))
	{
		fprintf(stderr, "不能打开文件%s\n", file);
		exit(EXIT_FAILURE);
	}

	// 开始进行可选读取
	printf("输入一个 0 - %d 的索引.\n", ARSIZE - 1);
	while (scanf("%d", &i) == 1 && i >= 0 && i < ARSIZE)
	{
		pos = (long)i * sizeof(double);  // 计算偏移量
		fseek(infile, pos, SEEK_SET);  // 定位到所选位置
		fread(&value, sizeof(double), 1, infile);
		printf("这里value的值为%f.\n", value);
		puts("输入下一个索引:");
	}
	fclose(infile);

	return 0;
}