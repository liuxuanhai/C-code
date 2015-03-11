// ÕÛ°ë¶ÔÆë
// 4 3 2 1 0 => 0 1 2 1 0
#include <stdio.h>
int main(void)
{
	int a[99];

	for (int i = 0; i < 99; i++)
		a[i] = 98 - i;

	for (int i = 0; i < 99; i++)
		printf("%d ", a[i]);
	printf("\n\n");

	for (int i = 0; i < 99; i++)
		a[i] = a[a[i]];

	for (int i = 0; i < 99; i++)
		printf("%d ", a[i]);
	printf("\n\n");

	return 0;
}