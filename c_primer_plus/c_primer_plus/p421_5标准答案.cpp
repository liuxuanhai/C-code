// 关于学生成绩的管理
#include <stdio.h>
#include <string.h>
#define LEN 14     // 学生姓氏和名字的长度限制
#define CSIZE 4    // 班级的学生个数
#define SCORES 3   // 成绩的科目个数

struct name {
	char first[LEN];
	char last[LEN];
};
struct student {
	struct name person;
	float scores[SCORES];
	float mean;
};

void get_scores (struct student ar[], int lim);
void find_means (struct student ar[], int lim);
void show_class (const struct student ar[], int lim);
void show_ave   (const struct student ar[], int lim);

int main (void)
{
	struct student cla[CSIZE] = {
		{"Flip", "Snide"},
		{"Clare", "Voyans"},
		{"Bingo", "Higgs"},
		{"Fawn", "Hunter"}
	};

	get_scores(cla, CSIZE);
	find_means(cla, CSIZE);
	show_class(cla, CSIZE);
	show_ave(cla, CSIZE);

	return 0;
}

void get_scores(struct student ar[], int lim)
{
	int i, j;
	for (i = 0; i < lim; i++)
	{
		printf ("Please enter %d scores for %s %s:\n",
			SCORES, ar[i].person.first, ar[i].person.last);
		for (j = 0; j < SCORES; j++)
		{
			while (scanf("%f", &ar[i].scores[j]) != 1)
			{
				scanf ("%*s");
				puts ("Please use numeric input.");
			}
		}
	}
}

void find_means (struct student ar[], int lim)
{
	int i, j;
	float sum;

	for (i = 0; i < lim; i++)
	{
		for (sum = 0, j = 0; j < SCORES; j++)
			sum += ar[i].scores[j];
		ar[i].mean = sum / SCORES;
	}
}

void show_class (const struct student ar[], int lim)
{
	int i, j;
	char wholename[2 * LEN];

	for (i = 0; i < lim; i++)
	{
		strcpy (wholename, ar[i].person.first);
		strcat (wholename, " ");
		strcat (wholename, ar[i].person.last);
		printf ("%27s: ", wholename);
		for (j = 0; j < SCORES; j++)
			printf ("%6.1f", ar[i].scores[j]);
		printf ("  Average = %5.2f\n", ar[i].mean);
	}
}

void show_ave (const struct student ar[], int lim)
{
	int i, j;
	float total;

	printf ("\n%27s: ", "QUIZ AVERAGES");
	for (j = 0; j < SCORES; j++)
	{
		for (total = 0, i = 0; i < lim; i++)
			total += ar[i].scores[j];
		printf ("%6.2f", total / lim);
	}
	putchar ('\n');
}