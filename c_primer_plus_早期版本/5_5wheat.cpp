//指数增长小程序 棋盘上的小麦数
//c primer plus 程序清单 5.5
//wheat.c -- 指数增长
#include <stdio.h>
#define SQUARES 64  //棋盘上的方格数
#define CROP 1E15  //美国每年小麦的产量
int main (void)
{
	double current,total;
	int count = 1;

	printf ("square      grains added      total grains      fraction of US total\n");
	total = current =1.0;  //开始是一粒
	printf ("%4d %18.2e %16.2e %19.2e\n", count, current, total,total/CROP);
	while (count < SQUARES)
	{
		count = count + 1;
		current = 2.0 * current;  //下一个方格的数量
		total = total +current;  //总的数量
		printf ("%4d %18.2e %16.2e %19.2e\n", count, current, total,total/CROP);
	}
	printf ("That's all.");
	return 0;
}