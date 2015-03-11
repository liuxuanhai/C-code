// p352 编程练习 6 统计1000个0-9的数产生的次数
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNT 1000
#define SIZE 10

int main (void)
{
	int ra[SIZE] = {0}, temp;
	int i;
	srand ((unsigned int) time (0));   // 这里为什么要放在for的外面??????????
	for (i = 0; i < COUNT; i++)
	{
		
		temp = rand () % 10;
		printf ("%3d", temp);
		if ((i + 1) % 23 == 0)        // i+1是为了防止0%23== 0的局面
			puts ("\n");
		ra[temp]++;
	}
	for (i = 0; i < SIZE; i++)
		printf ("\n%d -- >> %d\n", i, ra[i]);

	return 0;
}