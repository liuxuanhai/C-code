#include <stdio.h>
int main()
{
	int i,j,n,temp;
    int a[10];
	for(i=0;i<10;i++)
		scanf ("%d,",&a[i]);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10 - i - 1; j++)
			if (a[j] < a[j+1])
			{
				int temp2 = a[j];
				a[j] = a[j+1];
				a[j+1] = temp2;
			}
	for(i=0;i<10;i++)
	printf("%5d,",a[i] );
	printf("\n");
	return 0;
}
