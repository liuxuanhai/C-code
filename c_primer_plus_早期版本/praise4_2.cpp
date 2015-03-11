// c primer plus 程序清单4.2
//praise.c -- 使用不同类别的字符串  //praise 赞扬 称赞
#include <stdio.h>
#define PRAISE "What a super marvelous name!"  //marvelous 非凡的 不可思议的
int main ()
{
	char name[40];

	printf ("What's your name?\n");
	scanf ("%s",&name);                                                     //scanf()遇到第一个blank停止扫描 输入he shi xiong将只扫描he
	printf ("Hello,%s.%s\n",name,PRAISE);   
	return 0;
}