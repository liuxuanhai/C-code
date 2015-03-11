// p399 程序清单 14.12
#include <stdio.h>
#include <stdlib.h>

struct flex {
	int count;
	double average;
	double score[];  // 伸缩型数组成员 前面至少又一个普通成员
};

void showflex (struct flex * p);

int main (void)
{
	struct flex * pf1, * pf2;
	int n = 5;
	int i;
	double tot = 0;

	// 为结构和数组分配储存空间
	pf1 =(struct flex *) malloc (sizeof (struct flex) + n * sizeof(double));
	pf1 -> count = n;
	for (i = 0; i < n; i++)
	{
		pf1 -> score[i] = 20.0 - i;
		tot += pf1 -> score[i];
	}
	pf1 -> average = tot / n;

	showflex (pf1);

	// 与上次结构大小不同的结构
	n = 9;
	tot = 0;
	pf2 =(struct flex *) malloc (sizeof (struct flex) + n * sizeof(double));
	pf2 -> count = n;
	for (i = 0; i < n; i++)
	{
		pf2 -> score[i] = 20.0 - i / 2.0;
		tot += pf2 -> score[i];
	}
	pf2 -> average = tot / n;
	showflex (pf2);

	// 释放分配内存
	free (pf1);
	free (pf2);

	return 0;
}

void showflex (struct flex * p)
{
	int i;
	printf ("scores: ");
	for (i = 0; i < p -> count; i++)
		printf ("%g ", p -> score[i]);
	printf ("\naverage: %g\n", p -> average);
}