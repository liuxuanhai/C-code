//printf()和scanf()的*修饰符 4.4.6 (2)
//c primer plus 程序清单 4.17
//skip.c -- 跳过输入的头两个整数
#include <stdio.h>
int main ()
{
	int n;

	printf ("Please enter three integers: \n");
	scanf ("%*d %*d %d",&n);
	printf ("The last integer was %d\n",n);
	return 0;
}
//*修饰符使scanf()函数跳过相应的输入项目