#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void choujiang(int [], int, int);

int main(void)
{
	int ar[10];
	for (int i = 0; i < 10; i++)
		ar[i] = i+1;
	choujiang(ar, 10, 8);

	return 0;
}

void choujiang(int ar[], int arrSize, int num)
{
	int i, choice, temp;
	srand(time(0));
	if (num > arrSize)
	{

		puts("挑选的数量过大, 将回调到能显示的最大数量");
		num = arrSize;
	}
	for (i = 0; i < num; i++)
	{
		choice = rand() % (arrSize - 1);
		printf("%2d ", ar[choice]);
		if (i % 3 == 2)
			putchar('\n');
		temp = ar[choice];
		ar[choice] = ar[arrSize - 1];  // 对于数组中的每个数只能出现一次的随机选取, 把使用过的数放到数组结尾然后缩短数组是个不错的选择
		ar[arrSize - 1] = temp;
		arrSize--;
	}
	if (i % 20 != 0)
		putchar('\n');
}