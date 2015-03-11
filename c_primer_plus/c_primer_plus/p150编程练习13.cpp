#include <stdio.h>
#define SIZE 8

int main(void)
{
	double ar[SIZE], arr[SIZE], temp = 0;
	int i = 0, j;

	while(i < SIZE && 1 == scanf("%lf", &ar[i]))
		i++;
	
	for(j = 0; j < i; j++)
	{	
		printf("%9.2lf", ar[j]);
		temp += ar[j];
		arr[j] = temp;
	}
	putchar('\n');
	for(j = 0; j < i; j++)
		printf("%9.2g", arr[j]);
	putchar('\n');

	return 0;
}