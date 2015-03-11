// ±‡≥Ã¡∑œ∞ 9.11 (3)
#include <stdio.h>
void fun1(char, int, int);
int main(void)
{
	char ch = '#';
	int a = 5;
	int b = 3;

	fun1(ch, a, b);

	return 0;
}

void fun1(char ch, int a, int b)
{
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
			printf ("%c", ch);
		putchar('\n');
	}
}