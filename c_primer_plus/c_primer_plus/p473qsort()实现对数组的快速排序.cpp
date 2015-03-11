// 程序清单 16.15
#include <stdio.h>
#include <stdlib.h>

#define NUM 40
void fillarray (double ar[], int n);
void showarray (const double ar[], int n);
int mycomp (const void * p1, const void * p2);

int main (void)
{
	double vals[NUM];
	fillarray (vals, NUM);
	puts ("Random list: ");
	showarray (vals, NUM);
	qsort (vals, NUM, sizeof (double), mycomp); // vals为void类型的指针 所以系统要知道每个元素的大小所以有了第三个参数sizeof (double) 系统还要知道要比较的项目数(还有防止数组越界)所以要有第二个参数
	puts ("\nSorted list: ");
	showarray (vals, NUM);

	return 0;
}

void fillarray (double ar[], int n)
{
	int index;

	for (index = 0; index < n; index++)
		ar[index] = (double) rand () / ((double) rand () + 0.1);
}
void showarray (const double ar[], int n)
{
	int index;

	for (index = 0; index < n; index++)
	{
		printf ("%9.4f ", ar[index]);
		if (index % 6 == 5)
			putchar ('\n');
	}
	if (index % 6 != 0)
		putchar ('\n');
}

// 按从小到大的顺序进行排序
int mycomp (const void * p1, const void * p2)   // 如果第一个项目的值大于第二个项目的值 比较函数返回正数
{                                               // 如果相等 返回0
	const double * a1 = (const double *) p1;    // 如果小于 返回负数
	const double * a2 = (const double *) p2;
	                   // c中这种关于类型转换是否强制是可选的 但是c++则是必须的
	if (*a1 < *a2)
		return -1;
	else if (*a1 == *a2)
		return 0;
	else
		return 1;
}