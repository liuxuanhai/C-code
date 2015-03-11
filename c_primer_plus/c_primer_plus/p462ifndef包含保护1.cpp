// 程序清单 16.11 
#include <stdio.h>
#include "p462ifndef包含保护.h"
#include "p462ifndef包含保护.h" // 不小心两次包含同一个文件
int main ()
{
	names winner = {"Less", "Ismoor"};
	printf ("The winner is %s %s.\n", winner.first, winner.last);

	return 0;
}