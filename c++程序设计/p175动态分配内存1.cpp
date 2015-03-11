// 7-11 用new和delete动态内存分配方法,实现对任意数目输入整数的排序
#include <stdlib.h>
#include <stdio.h>

void sortArray1 (int [], int);

int main (void)
{
	int num;
	int i;
	int * a;

	printf ("请输入要进行排序的整数数目:\n");
	scanf_s ("%d", &num);
	//printf ("请输入要排序的个数:\n");
	//scanf ("%d", &num);

	// 动态分配数组内存
	a = new int[num];
	if (NULL == a)
	{
		printf ("内存出错!");
		return 0;
	}

	printf ("请输入要排序的整数:\n");
	for (i = 0; i < num; i++)
		scanf_s ("%d", &a[i]);

	sortArray1(a, num);

	for (i = 0; i < num; i++)
		printf (" %d ", a[i]);

	return 0;
}

void sortArray1 (int p[], int len)  // 此处的int p[]其实是个地址值
{
	for (int i = 0; i < len - 1; i++)
		for (int index = i + 1; index < len; index++)
			if (p[i] > p[index])
			{
				int hold = p[i];
				p[i] = p[index];
				p[index] = hold;
			}
}