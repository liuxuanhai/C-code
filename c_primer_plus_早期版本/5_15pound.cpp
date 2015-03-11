//带有参数的函数
//c primer plus 程序清单5.15
//pound.c --  定义一个带有参数的函数
#include <stdio.h>
void pound (int n);  //ANS风格的原型
int main (void)
{
	int times = 5;
	char ch = '!';
	float f = 6.0;
	pound (times);
	pound (ch);
	pound ((int)f);
	return 0;
}
void pound (int n)
{
	while (n-- > 0)
		printf ("#");
	printf ("\n");
}