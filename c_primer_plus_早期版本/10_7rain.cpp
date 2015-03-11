// 二维数组
// c primer plus 程序清单 10.7 p252
// rain.c -- 针对若干年的降水数据,计算年降水总量,年降水均量,以及月降水平均量
#include <stdio.h>
#define MONTHS 12                       // 一年的月份数
#define YEARS 5                         // 降水量数据的年数
int main (void)
{
	// 把数组初始化为2000年到2004年的降水量数据
	const float rain[YEARS][MONTHS] = {                             // const 告诉系统数据不能被修改 为常量
	{4.3f,4.3f,4.3f,3.0f,2.0f,1.2f,0.2f,0.2f,0.4f,2.4f,3.5f,6.6f},  // 不加f不能运行!!!!!!!!!!!为什么????????????
	{8.5f,8.2f,1.2f,1.6f,2.4f,0.0f,5.2f,0.9f,0.3f,0.9f,1.4f,7.3f},
	{9.1f,8.5f,6.7f,4.3f,2.1f,0.8f,0.2f,0.2f,1.1f,2.3f,6.1f,8.4f},
	{7.2f,9.9f,8.4f,3.3f,1.2f,0.8f,0.4f,0.0f,0.6f,1.7f,4.3f,6.2f},
	{7.6f,5.6f,3.8f,2.8f,3.8f,0.2f,0.0f,0.0f,0.0f,1.3f,2.6f,5.2f}
	};
	int year, month;
	float subtot, total;

	printf ("YEAR   RAINFALL (inches) \n");
	for (year = 0, total = 0; year < YEARS; year++)
	{                 
		for (month = 0, subtot = 0; month < MONTHS; month++)
			subtot += rain[year][month];  // 一年的降水量
		printf ("%5d %15.1f\n", 2000 + year, subtot);
		total += subtot;                  // 五年的总降水量
	}
	printf ("\nThe yearly average is %.1f inches.\n\n", total/YEARS);  // 每年的平均量
	printf ("MONTHLY AVERAGES:\n\n");
	printf (" Jan  Feb  Mar  Apr  May  Jun  Jul  Aug  Sep  Oct  Nov  Dec\n");

	for (month = 0; month < MONTHS; month++)
	{
		for (year = 0, subtot = 0; year < YEARS; year++)
			subtot += rain[year][month];  // 五年内每年相同月份的降水量总和
		printf ("%4.1f ", subtot/YEARS);
	}
	printf ("\n");

	return 0;
}