// 7-10 用malloc(买哦唠嗑,动态内存)和free动态内存分配方法,实现对任意数目输入整数的排序
#include <stdlib.h>
#include <stdio.h>

void sortArray (int[], int);  // 数组排序函数

int main (void)
{
	int * a;                               // a为一个地址,为下边把动态分配的数组首地址赋给a做铺垫
	int i, num;

	// 输入要排序的整数数目
	printf ("请输入要进行排序的整数数目:\n");
	scanf_s ("%d", &num);

	// 动态分配数组,保存输入的整数
	a = (int * )malloc(sizeof(int) * num); // 此处是把这块内存给了a而不是把这块内存的地址给了a
	if (NULL == a)
	{
		printf ("内存出错!");
		return 0;
	}

	// 输入拟排序的整数
	printf ("请输入要进行排序的整数:\n");
	for (i = 0; i < num; i++)	
		scanf ("%d", &a[i]);

	// 调用排序函数排序
	sortArray(a, num);

	// 输出排序后的结果
	printf ("排序结果如下:\n");
	for (i = 0; i < num; i++)
		printf (" %d ", a[i]);

	// 释放动态分配的空间
	free (a);
}

void sortArray (int a[], int len)
{
	for (int pass = 0; pass < len - 1; pass++) // 此处初始化pass的时候进行了声明
		for (int i = pass + 1; i < len; i++)
			if(a[pass] > a[i])
			{
				int hold;
				hold = a[pass];
				a[pass] = a[i];
				a[i] = hold;
			}
}