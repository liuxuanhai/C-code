//循环简介 
//c primer plus 程序清单 5.2
//shoes.c -- 计算多个鞋尺码对应的英寸长度
#include <stdio.h>
#define ADJUST 7.64
#define SCALE 0.325
int main ()
{
	double shoe, foot;

	printf ("Shoes size (men's)	   foot length\n");
	shoe = 3.0;
	while (shoe < 18.5)
	{
		foot = SCALE*shoe + ADJUST;
		printf ("%10.1f %20.2f inches\n", shoe, foot);
		shoe = shoe + 1.0;
	}
	printf ("If the shoe fits, wear it.\n");
	return 0;
}