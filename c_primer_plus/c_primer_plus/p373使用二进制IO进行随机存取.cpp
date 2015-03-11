// p373 程序清单 13.7
#include <stdio.h>
#include <stdlib.h>
#define ARSIZE 1000

int main (void)
{
	double numbers[ARSIZE];
	double value;
	const char * file = "p373numbers.dat";
	int i;
	long pos;
	FILE * iofile;

	// 创建一组double类型的数值
	for (i = 0; i < ARSIZE; i++)
		numbers[i] = 100.0 * i + 1.0 / (i + 1);
	// 尝试打开文件供写入
	if (NULL == (iofile = fopen (file, "wb")))
	{
		fprintf (stderr, "不能打开%s文件.\n", file);
		exit (1);
	}
	// 把数组中的数据以二进制形式写进文件
	fwrite (numbers, sizeof (double), ARSIZE, iofile);
	fclose (iofile);
	// 尝试打开文件供读取
	if (NULL == (iofile = fopen (file, "rb")))
	{
		fprintf (stderr, "不能打开%s文件.\n", file);
		exit (1);
	}
	// 从文件中读取所选项目
	printf ("输入一个 0 - %d 的索引.\n", ARSIZE - 1);
	scanf ("%d", &i);
	while (i >= 0 && i < ARSIZE)
	{
		pos = (long)i * sizeof (double);  // 计算偏移量
		fseek (iofile, pos, SEEK_SET);    // 在文件中定位到那里
		fread (&value, sizeof (double), 1, iofile);
		printf ("这里value的值为%f.\n", value);
		puts ("输入下一个索引:");
		scanf ("%d", &i);
	}
	fclose (iofile);
	puts ("ok!");

	return 0;
}