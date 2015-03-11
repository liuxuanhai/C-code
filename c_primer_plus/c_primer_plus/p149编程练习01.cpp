// ±‡≥Ã¡∑œ∞ 6.16
#include <stdio.h>
#define SIZE 26
int main(void)
{
	char array[SIZE];

	for(int i = 0; i < SIZE; i++)
		array[i] = 'a' + i;
	for(int i = 0; i < SIZE; i++)
		printf("%c\n", array[i]);

	return 0;
}