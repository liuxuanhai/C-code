// ±‡≥Ã¡∑œ∞ 5
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int ar[100];

	srand(int(time(0)));
	for (int i = 0; i < 100; i++)
		ar[i] = rand() % 10;

	for (int i = 0; i < 99; i++)
		for (int j = i; j < 100; j++)
			if (ar[i] < ar[j])
			{
				int temp;
				temp = ar[i];
				ar[i] = ar[j];
				ar[j] = temp;
			}
	int i;
	for ( i = 0; i < 100; i++)
	{
		printf("%d ", ar[i]);
		if (i % 10 == 9)
			putchar('\n');
	}
	if (i % 10 != 0)
		putchar('\n');
	return 0;
}