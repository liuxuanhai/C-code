// ±‡≥Ã¡∑œ∞ 11.13 (9)
#include <stdio.h>
#include <ctype.h>
#include <string.h>
char * del_space(char *);
int main(void)
{
	char str[81];

	while (gets(str) && str[0] != '\0')
		puts(del_space(str));

	return 0;
}

char * del_space(char * str)
{
	int i = 0, j = 0;
	char temp[81];
	while (str[i])
		if (!isspace(str[i]))
			temp[j++] = str[i++];
		else
			i++;
	temp[j] = '\0';
	strcpy(str, temp);
	return str;
}