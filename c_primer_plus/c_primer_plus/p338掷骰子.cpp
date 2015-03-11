// p338 程序清单 12.11
#include <stdio.h>
#include <stdlib.h>       // 为rand()提供类库
#include "p339掷骰子.h"     // ""指示编译器在本地寻找文件

int roll_count = 0;       // 外部链接
extern int iii;
static int rollem (int sizes)       // 这个文件的私有函数
{
	int roll;

	roll = rand() % sizes +1;
	roll_count++;                   // 记录函数调用的次数

	return roll;
}

int roll_n_dice (int dice, int sides)
{
	int d;
	int total = 0;
	
	if (sides < 2)
	{
		puts ("骰子的面数至少为2!");
	
		return -2;
	}
	if (dice < 1)
	{
		puts ("至少有1个骰子!");

		return -1;
	}
	for (d = 0; d < dice; d++)
		total += rollem(sides);
	ii = 321;
	iii = 222;
	printf ("roll_n_dece:ii->>%d, iii = %d", ii, iii);
	return total;
}