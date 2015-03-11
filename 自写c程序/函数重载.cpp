#include <stdio.h>

void aaa (int i);
void aaa (int, int);

int main (void)
{
	int a = 1, b = 2, c = 3;

	puts ("a:");
	aaa (a);
	puts ("bc:");
	aaa (b, c);

	return 0;
}

void aaa (int a)
{
	printf ("a:%d\n", a);
}
void aaa (int b, int c)
{
	printf ("b:%d c:%d", b, c);
}