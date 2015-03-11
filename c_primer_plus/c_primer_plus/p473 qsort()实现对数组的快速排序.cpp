// 程序清单 16.15
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 40

void fillArray(double ar[], int n);
void showArray(const double ar[], int n);
int myComp(const void * pl, const void * p2);

int main(void)
{
	double vals[NUM];
	srand(time(0));
	fillArray(vals, NUM);
	puts("Random list: ");
	showArray(vals, NUM);
	qsort(vals, NUM, sizeof(double), myComp);
	puts("\nSorted list: ");
	showArray(vals, NUM);

	return 0;
}

void fillArray(double ar[], int n)
{
	for (int i = 0; i < n; i++)
		ar[i] = (double)rand() / ((double)rand() + 0.1);
}

void showArray(const double ar[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%9.4f ", ar[i]);
		if (i % 6 == 5)
			putchar('\n');
	}
	if (i % 6 != 0)
		putchar('\n');
}

// 从小到大的顺序
int myComp(const void * p1, const void * p2)
{
	const double * a1 = (const double *)p1;  // c中可选 c++是必须的
	const double * a2 = (const double *)p2;
	if (*a1 < *a2)
		return -1;
	else if (*a1 == *a2)
		return 0;
	else
		return 1;
}