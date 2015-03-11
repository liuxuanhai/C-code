// p297 程序清单 11.13
#include <stdio.h>
#include <string.h>
void fit (char *, unsigned int);

int main (void)
{
	char mesg[] = "Hold on to your hats, hacter!";

	puts (mesg);
	fit (mesg, 7);  // 把"on to"中间的空格换成了'\0'
	puts (mesg);
	puts ("Let's look at more of the string. ");
	puts (mesg + 8);

	return 0;
}

void fit (char * string, unsigned int n)
{
	if (strlen(string) > n)
		*(string + n) = '\0';

	return;
}