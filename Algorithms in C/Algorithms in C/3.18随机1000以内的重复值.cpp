#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

int main(void)
{
	int ar[N];

	for (int i = 0; i < N; i++)
		ar[i] = 0;

	srand((unsigned long)time(0));
	for (int i = 1; 1; i++)
	{	
		int temp = rand() % N;
		if(!ar[temp])
			ar[temp] = 1;
		else
		{
			printf("%d", i);
			break;
		}
	}

	return 0;
}