// 编程练习 11.13 (10)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void show_menu(void);
char getlet(const char *);
void show(char *[], int);
void ascii(char **, int);
void length(char **, int);
void fir_word(char **, int);
bool fir(char *, char *);
int main(void)
{
	char ch;
	char * str[5] = {
		{"All our dreams can come true!"},
		{"If we have the courage to pursue them."},
		{"How are you?"},
		{"I am fine, thanks."},
		{"And you?"}
	};

	show_menu();
	while (ch = getlet("abcde"))
	{
		switch (ch)
		{
			case 'a': show(str, 5);break;
			case 'b': ascii(str, 5);show(str, 5);break;
			case 'c': length(str, 5);show(str, 5);break;
			case 'd': fir_word(str, 5);show(str, 5);break;
			case 'e': exit(EXIT_SUCCESS); break;
			default:
				break;
		}
		show_menu();
	}

	return 0;
}
void show_menu(void)
{
	printf("\na.show original\t\t\tb.show with ascii\n");
	printf("c.show as length\t\td.show as the first word length\n");
	puts("e.quit");
}
char getlet(const char * s)
{
	char ch;
	while (ch = getchar())
	{
		while (getchar() != '\n')
			continue;
		if (NULL == strchr(s, ch))
			printf("请输入%s中的一个字符:\n", s);
		else
			break;
	}
	return ch;
}
void show(char ** s, int n)
{
	int i = 0;
	while (i < n)
		puts(s[i++]);
}
void ascii(char **s, int n)
{
	char *temp;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (strcmp(s[i], s[j]) > 0)
			{
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
}
void length(char ** s, int n)
{
	char *temp;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (strlen(s[i]) > strlen(s[j]))
			{
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
}
void fir_word(char ** s, int n)
{
	char *temp;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (fir(s[i], s[j]))
			{
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
}
bool fir(char * s1, char * s2)
{
	int i = 0, j = 0;
	while (s1[i] != ' ')
		i++;
	while (s2[j] != ' ')
		j++;
	
	return i > j;
}