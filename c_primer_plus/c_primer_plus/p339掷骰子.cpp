// p339 程序清单 12.13 
#include <stdio.h>
#include <stdlib.h>        // 为rand()提供函数原型
#include <time.h>          // 为time()提供函数原型
#include "p339掷骰子.h"	   // 为roll_n_dice()和roll_count提供函数原型

int iii = 333;

int main (void)
{
	int dice, roll;
	int sides;

	srand ((unsigned int) time (0));    // 随机化种子
	puts ("输入骰子的面数(输入0退出):");
	while (scanf ("%d", &sides) == 1 && sides > 0)
	{
		puts ("要掷几个骰子?");
		scanf ("%d", &dice);
		roll = roll_n_dice (dice, sides);
		printf ("你掷出了%d点, 用的是%d个%d面的骰子.\n", roll, dice, sides);
		puts ("输入骰子的面数(输入0退出):");
	}
	printf ("这次你一共掷了%d个骰子.\n", roll_count);
	puts ("ok!");
	printf ("main:ii->>%d, iii - >> %d", ii, iii);
	return 0;
}