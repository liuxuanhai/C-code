#include <stdio.h>
#define SIZE 8

int main(void)
{
	int ar[SIZE];
	int temp = 1;

	for(int i = 0; i < SIZE; i++)
		ar[i] = (temp *= 2);

	int i = 0;
	do
	{	
		printf("%d\n", ar[i]);
		i++;
	}while(i < SIZE);

	return 0;
}