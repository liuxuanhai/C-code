// p421 编程练习 14.18 (2)
#include <stdio.h>

struct ymd {
	int year;
	int month;
	int day;
};

enum mon {January = 1, February, March, April, May, June, July, August, September, October, November, December};

void get_ymd (struct ymd *);     // 年月日的写入           传结构指针
int Days_year (int);             // 一年的天数
int Days_someday (struct ymd);   // 一年开始到某天的天数   传结构副本
int totday (struct ymd, struct ymd);

int main (void)
{
	struct ymd birthday;
	struct ymd today;

	puts ("请输入你的生日:");
	get_ymd (&birthday);
	puts ("请输入现在的时间:");
	get_ymd (&today);
	printf ("加上没过完的今天你一共活了%d天了!\n", 
						totday (birthday, today));

	return 0;
}

void get_ymd (struct ymd * st)
{
	printf ("Year :");
	scanf ("%d", &st -> year);
	printf ("Month:");
	scanf ("%d", &st -> month);
	printf ("Day  :");
	scanf ("%d", &st -> day);
}

int Days_year (int year)
{
	if (year % 4 == 0)   // 闰年 366天
		return 366;
	else
		return 365;
}

int Days_someday (struct ymd st)
{
	int temp = 0;
	int i;
	for (i = January; i < st.month; i++)
	{
		if (i == 4 || i == 6 || 
			i == 9 || i == 11)
			temp += 30;
		else if (i == 2 && st.year % 4 == 0)
			temp += 29;
		else if (i == 2 && st.year % 4 != 0)
			temp += 28;
		else
			temp += 31;	
	}

	return (temp + st.day);
}

int totday (struct ymd birthday, struct ymd today)
{
	int totday = 0;
	int i;

	for (i = birthday.year; i < today.year; i++)
		totday += Days_year (i);
	
	totday += Days_someday (today);
	totday -= Days_someday (birthday);

	return totday;
}