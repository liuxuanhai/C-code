// 编程练习 11.13 (1)
#include <stdio.h>
#define SIZE 11

char * read_n(char *, int);

int main()
{
	char ar[SIZE];
	printf("输入一行字符, 我将会把前%d个存进数组:\n", SIZE - 1);
	if (NULL == read_n(ar, SIZE - 1))
		puts("Input failed!");
	else
		puts(ar);

	return 0;
}
char * read_n(char * ar, int n)
{
	int i = 0;
	char ch;
	
	while ((ch = getchar()) != EOF)
		if (i < n)
			ar[i++] = ch;
	if (ch == EOF && i < n)
		return NULL;          // 意思是在读入n被字符之前使用EOF会导致返回值为NULL并且不会为数组尾部加上'\0'
	else
		ar[i] = '\0';
	
	return ar;
}