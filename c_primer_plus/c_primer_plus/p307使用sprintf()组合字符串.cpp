// p307 程序清单 11.24
#include <stdio.h>
#include <string.h>
#define SIZE 20

int main (void)
{
	char first[SIZE];
	char sp[SIZE * 2 + 10];// * sp; 这里用指针是不对的.用指针只为指针分配一个地址空间, 而这里是将组合后的字符串放到了以sp为首元素的一块内存里面
	char last[SIZE];
	float prize;

	puts ("你的姓氏是?");
	gets (first);
	puts ("你的名字是?");
	gets (last);
	puts("你获得的奖金是多少?");
	scanf ("%f", &prize);
	sprintf (sp, "%s, %-19s%: $%6.2f\n", first, last, prize);
	puts (sp);

	return 0;
}