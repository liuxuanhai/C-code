// ±‡≥Ã¡∑œ∞ 10.13 (5)
#include <stdio.h>
#define SIZE 6
double fun1(double [], int);
int main()
{
	double arr[SIZE] = {2.5, 2.4, 6.8, 3.4, 6.4, 8.2};
	printf("%g\n", fun1(arr, SIZE));

	return 0;
}
double fun1(double ar[], int n)
{
	int i;
	double min = ar[0], max = ar[0];
	for (i = 1; i < n; i++)
	{
		if (min > ar[i])
			min = ar[i];
		else if (max < ar[i])
			max = ar[i];
	}
	return max - min;
}