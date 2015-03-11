//c primer plus 程序清单 4.9 使用修饰符和标志示例(3)
//flags(旗,标示).c -- 一些格式标志的使用示例
#include <stdio.h>
int main ()
{
	printf ("%x %X %#x\n",31,31,31);
	printf ("**%d**% d**% d**\n",42,42,-42);  //使用空格使正值前产生一个前导空格,负值不加前导空格
	printf ("**%5d**%5.3d**%05d**%05.3d**\n",6,6,6,6);
	return 0;
}