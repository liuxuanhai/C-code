// ±‡≥Ã¡∑œ∞ 6.16 3
#include <stdio.h>
int main(void)
{
	char ch = 'F';

	for(int i = ch; i >= 'A'; i--)
	{
		for(int j = ch; j >= i; j--)
			putchar(j);
		putchar('\n');
	}

	return 0;
}