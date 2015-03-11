// p300 程序清单 11.16 strcmp("A", "D"):返回值为负数(int(A - B))ascii码的操作
// string comparison
// 注意: 大写字母的ascii码在小写字母前面, 本c的实现只返回-1, 0, 1这三个值
#include <stdio.h>
#include <string.h>
#define ANSWER "heshixiong"

int main (void)
{
	char ty[40];
	int num;

	puts ("Who writes this program ?");
	gets (ty);
	while ((num = strcmp (ty, ANSWER)) != 0)  // 如果直接写ANSWER == try是错的 因为这是两个地址
	{
		printf ("%d", num);
		puts ("Wrong, try again!");
		gets (ty);
	}
	puts ("Right!");

	return 0;
}