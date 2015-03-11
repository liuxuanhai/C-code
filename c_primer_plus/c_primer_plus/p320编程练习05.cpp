// 编程练习 11.13 (5)
#include <stdio.h>
#include <ctype.h>
#define TEXT "This is a text line."

bool is_within(char, const char *);

int main(void)
{
	char ch;

	while ((ch = getchar()) != EOF)
	{
		if (!isalpha(ch))
			continue;
		if (is_within(ch, TEXT))
			printf("%c在%s中.\n", ch, TEXT);
		else
			printf("%c不再%s中.\n", ch, TEXT);
	}
	puts("Done!");

	return 0;
}

bool is_within(char ch, const char * ar)
{
	while (*ar)
		if (*ar++ == ch)
			return true;
	return false;
}