// 编程练习 11.13 (15)
// 命令行执行相应命令
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void show(char *);
int main(int argc, char *argv[])
{
	char ar[91];
	int i = 0, j = 0;
	char ch;
	while (EOF != (ch = getchar()))
		ar[i++] = ch;
	ar[i] = '\0';
	if (argc != 2  || argv[1][0] != '-')
	{
		puts("无法识别的命令.");
		getchar();
		exit(EXIT_FAILURE);
	}
	else
		switch (argv[1][1])
	{
		case 'p': show(ar);break;
		case 'u': 
			while (ar[j])
			{
				ar[j] = toupper(ar[j]);
				j++;
			}
			show(ar);
			break;
		case 'l': 
			j = 0; 
			while (ar[j])
			{
				ar[j] = tolower(ar[j]);
				j++;
			}
			show(ar);
			break;
		default:
			puts("无法识别的命令.");
			getchar();
			exit(EXIT_FAILURE);
			break;

	}
	getchar();
	return 0;
}
void show(char * ar)
{
	int i = 0;
	while (ar[i])
		putchar(ar[i++]);
}