// 编程练习 (5) 抽奖程序
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
void choice_array (int size, int n);
int main (void)
{
	puts ("获奖的选手为:");
	choice_array (SIZE, 5);

	return 0;
}

void choice_array (int size, int n)
{
	int temp[SIZE] = {0};
	int j, k = 0, c;
	srand ((unsigned int) time (0));
	for (int i = 0; i < n; i++)
	{
		k = 0;
		c = rand () % 100 + 1;
		for (j = 0; j < 20; j++)
		{
			if (temp[j] == c)
			{
				i--;
				k = 1;
				break;
			}
		}
		if (0 == k)
		{	
			printf (" %d ", c);
			temp[i] = c;
		}
	}
}