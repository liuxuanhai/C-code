// 程序清单 14.12
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct flex
{
	int count;
	double average;
	double scores[];  // 伸缩型的数组成员
};

void showflex(const struct flex *);

int main(void)
{
	struct flex * pf1, * pf2;
	int n = 5;
	int i;
	double tot = 0;

	pf1 = (struct flex *) malloc(sizeof(struct flex) + sizeof(double) * n);
	//printf("%d", sizeof(*pf1));// 其实结果还是16
	pf1->count = n;
	for (i = 0; i < n; i++)
	{
		pf1->scores[i] = 20.0 - i;
		tot += pf1->scores[i];
	}
	pf1->average = tot / n;
	showflex(pf1);

	n = 9;
	pf2 = (struct flex *) malloc(sizeof(struct flex) + sizeof(double) * n);
	//printf("%d", sizeof(*pf1));// 其实结果还是16
	pf2->count = n;
	for (i = 0; i < n; i++)
	{
		pf2->scores[i] = 20.0 - i;
		tot += pf2->scores[i];
	}
	pf2->average = tot / n;
	showflex(pf2);

	return 0;
}

void showflex(const struct flex * fl)
{
	int i;
	printf("scores: ");
	for (i = 0; i < fl->count; i++)
		printf("%g ", fl->scores[i]);
	printf("\naverage: %g \n", fl->average);
}