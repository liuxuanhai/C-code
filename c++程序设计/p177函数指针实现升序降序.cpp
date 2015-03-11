// p177 函数指针实现升序降序                                             // 函数指针指向的是代码区
#include <stdio.h>                                                       // 普通变量指针指向的是数据存储区
#include <stdlib.h>

bool ascending (int, int);                         // 升序判断函数
bool decending (int, int);                        // 降序判断函数
void sortArray (int [], int, bool (*)(int, int));  // 排序函数
void displayArray (int [], int);

int main (void)
{
	int * a;
	int i, num;

	// 输入要排序的整数数目
	printf ("请输入要排序的整数数目:\n");
	scanf ("%d", &num);

	// 动态分配内存
	a = new int[num];
	if (NULL == a)
	{
		printf ("内存错误!");
		return 0;
	}

	// 输入拟排序的整数
	printf ("请输入要排序的整数:\n");
	for (i = 0; i < num; i++)
		scanf ("%d", &a[i]);

	// 进行升序排序
	sortArray (a, num, ascending);

	// 输出a排序后的结果
	printf ("升序排序后:\n");
	for (i = 0; i < num; i++)
		printf (" %d ", a[i]);
	printf ("\n");

	// 使用descending对a进行排序
	sortArray (a, num, decending);
	
	// 输出a排序后的结果
	printf ("降序排序后:\n");
	for (i = 0; i < num; i++)
		printf (" %d ", a[i]);
	printf ("\n");

	// 释放动态分配的空间
	delete [] a;

	return 0;
}

bool ascending (int a, int b)
{
	return (a < b);
}

bool decending (int a, int b)
{
	return (a > b);
}

void sortArray (int b[], int len, bool (*compare) (int, int))
{
	for (int pass = 0; pass < len - 1; pass++)
		for (int i = pass + 1; i < len; i++)
			if (!(*compare)(b[pass], b[i])) 
			{
				int temp;
				temp = b[pass];
				b[pass] = b[i];
				b[i] = temp;
			}
}