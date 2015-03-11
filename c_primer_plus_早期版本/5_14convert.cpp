//类型的自动转换
//c primer plus 程序清单 5.14
//convert.c -- 自动类型转换
#include <stdio.h>
int main ()
{
	char ch;
	int i;
	float f1;

	f1 = ch = i = 'C';  //C被作为1字节的ASCII值储存在ch里;C转换成整数67,以4个字节储存在i里;

	printf ("ch = %c, i = %d, f1 = %2.2f\n", ch, i, f1);
	ch = ch + 1;  //作为函数的参数传递时,char和short会被转换成int
	i = f1 + 2 * ch;  //赋值时'='右边的数据类型统一跟随左边的
	f1 = 2.0 * ch + i;
	printf ("ch = %c, i = %d, f1 = %2.2f\n", ch, i, f1);
	ch = 5212205.17;
	printf ("Now ch = %c\n",ch);  //ch为一个很大的数 在降级截取高位后 ch最终变成了'-'的ascii码
	return 0;
}