//嵌套循环 
//c primer plus 程序清单 6.17 
//rows.c -- 使用嵌套循环  //外循环为行,内循环为列
#include <stdio.h>
#define ROWS 6 //有六行
#define CHARS 10 //有十个字符 十列
int main (void)
{
	int rows;
	char ch;

	for (rows = 1; rows <= ROWS; rows++)
	{
		for (ch = 'A'; ch < ('A'  + CHARS); ch++)
		{
			printf ("%c",ch);
		}
		printf ("\n");
	}

}