// p421 编程练习 14.18 (1)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct month {
	char name[10];      // 月份明
	char abbrev[4];	    // 缩写
	int days;           // 天数
	int monumb;         // 编号
};

char * _itoa (int);

const struct month months[12] = {
	{"January", "Jan", 31, 1},
	{"February", "Feb", 28, 2},
	{"March", "Mar", 31, 3},
	{"April", "Apr", 30, 4},
	{"May", "May", 30, 5},
	{"June", "Jun", 30, 6},
	{"July", "Jul", 31, 7},
	{"August", "Aug", 31, 8},
	{"September", "Sep", 30, 9},
	{"October", "Oct", 31, 10},
	{"November", "Nov", 30, 11},
	{"December", "Dec", 31, 12}
};

int days (char * m);

int main (void)
{
	char input[20];
	int daytotal;

	printf ("输入月份:\n");
	while (gets (input) != NULL && input[0] != '\0')
	{
		daytotal = days(input);
		if (daytotal > 0)
			printf ("%s 有 %d 天!\n", input, daytotal);
		else
			printf ("错误输入!\n");
	}
	puts ("ok!");

	return 0;
}

int days (char * m)
{
	int total = 0;
	int mon_num = 0;
	int i;

	if (m[0] == '\0')
		total = -1;
	else
	{
		m[0] = toupper (m[0]);
		for (i = 1; m[i] != '\0'; i++)
			m[i] = tolower(m[i]);
		for (i = 0; i < 12; i++)
			if (strcmp (m, months[i].name) == 0 || 
				strcmp (m, months[i].abbrev) == 0 ||
				strcmp (m, _itoa (months[i].monumb)) == 0)
			{
				mon_num = months[i].monumb;
				break;
			}
		if (mon_num == 0)
			total = -1;
		else
			for (i = 0; i < mon_num; i++)
				total += months[i].days;
	}
	return total;
}

char * _itoa (int i)
{
	static char ch[20];

	itoa (i, ch, 10);
	
	return ch;
}