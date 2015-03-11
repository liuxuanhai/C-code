// p249 程序清单10.6 数组中的越界
#include <stdio.h>
int main (void)
{
	int v1 = 44;
	int a[4];
	int v2 = 88;
	int i;

	printf ("v1 = %d, v2 = %d\n", v1, v2);

	for (i = -1; i < 7; i++)
		a[i] = 2 * i + 1;

	for (i = -1; i < 7; i++)
		printf ("%3d%5d\n", i, a[i]);

	printf ("v1 = %d, v2 = %d\n", v1, v2);

	return 0;
}