// 编程练习 11.13 (6)
// 一个和strncpy()一样的函数
// strncpy(s1, s2, n)从s2复制n个字符给s1, 并在必要时截断s2或为其填充额外的空字符, 如果s2的长度等于大于n, 目标字符串就没有标志结束的空字符, 函数返回s1;
#include <stdio.h>
#include <string.h>
#define SIZE 80
char * strncpy_make(char *, char *, int);
int main(void)
{
	char s1[SIZE];
	char s2[SIZE];
	
	gets(s1);
	gets(s2);
	strncpy_make(s1, s2, 10);
	puts(s1);

	return 0;
}

char * strncpy_make(char * s1, char * s2, int n)
{
	int i;
	for (i = 0; i < n; i++)
		s1[i] = s2[i];
	if (i < n)
		s1[i] = '\0';
	return s1;
}