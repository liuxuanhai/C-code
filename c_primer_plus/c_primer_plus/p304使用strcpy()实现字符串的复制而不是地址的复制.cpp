// p303 程序清单 11.21  strcpy();将返回第一个参数的地址! 复制时会把第二个字符串的'\0'也复制上
#include <stdio.h>
#include <string.h>
#define LIM 3
#define SIZE 40

int main (void)
{
	char qwords[LIM][SIZE];
	char temp[SIZE];
	int i = 0;

	puts ("输入3个以q开始要进行复制的字符串.");
	while (i < LIM && gets(temp))
	{
		if (temp[0] == 'q')
		{
			strcpy (qwords[i], temp);
			i++;
		}
		else
		{
			puts ("你输入的不是以q开头的字符串,请重新输入:");
			// gets(temp);
		}
	}

	for (i = 0; i < LIM; i++)
		puts (qwords[i]);

	return 0;
}