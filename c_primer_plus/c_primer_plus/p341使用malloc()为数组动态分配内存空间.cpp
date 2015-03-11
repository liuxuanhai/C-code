// p341 程序清单 12.14
#include <stdio.h>
#include <stdlib.h>         // 为malloc(), free()和exit()提供函数原型

int main (void)
{
	double * ptr;
	int max;
	int number;
	int i = 0;

	puts ("请输入数组的最大个数:");
	scanf ("%d", &max);
	ptr = (double *) malloc (max * sizeof (double));

	if (NULL == ptr)
	{
		puts ("内存分配错误!");
		exit (EXIT_FAILURE);      // 异常终止程序
	}
	// ptr现在指向有max个元素的数组
	puts ("请输入数组元素(q退出)");
	while (i < max && scanf ("%lf", &ptr[i]))
		i++;
	puts ("你的输入如下:");
	number = i;                  // 这条语句的作用是输入了多少个就显示多少个
	for (i = 0; i < number; i++)
	{
		printf ("%7.2f", ptr[i]);
		if (i % 7 == 6)          // 显示的时候6个一行
			puts ("\n");
	}
	puts ("ok!");
	free (ptr);

	return 0;
}