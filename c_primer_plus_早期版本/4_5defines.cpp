// c primer plus 程序清单 4.5
// defines.c -- 使用limit.h和float.h中定义的常量
#include <stdio.h>
#include <limits.h>  //整数限制
#include <float.h>  //浮点数限制
int main ()
{
	printf ("Some number limits for this system:\n");
	printf ("Biggest int: %d\n",INT_MAX);
	printf ("One byte = %d bits on this system.\n",CHAR_BIT);
	return 0;
}
