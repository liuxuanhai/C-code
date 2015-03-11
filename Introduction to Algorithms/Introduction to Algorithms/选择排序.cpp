#include <stdio.h>

#define Num 10
#define X	5
#define Y	5

int main(void)
{
	int i, j, temp;
	int ar[Num] = {5, 3, 5, 1, 2, 6, 7, 3, 6, 3};
	int arr[5][5] = {
		2, 3, 5, 67, 1,
		6, 7, 8, 2, 5,
		1, 5, 8, 32, 1,
		7, 8, 3, 4, 6,
		3, 1, 6, 7, 5};

	// 一位数组排序 选择排序
	for (i = 0; i < Num - 1; i++)
		for (j = i + 1; j < Num; j++)
			if (ar[i] > ar[j])  // 这里写 < 就是从大到小排序
			{
				temp  = ar[i];
				ar[i] = ar[j];
				ar[j] = temp;
			}

	for (i = 0; i < Num; i++)
		printf("%d ", ar[i]);

	printf("\n\n");

	// 二维数组排序
	for (i = 0; i < X * Y - 1; i++)
		for (j = i + 1; j < X * Y; j++)
			if (arr[i/5][i%5] > arr[j/5][j%5])  // 这里写 < 就是从大到小排序
			{
				temp  = arr[i/5][i%5];
				arr[i/5][i%5] = arr[j/5][j%5];
				arr[j/5][j%5] = temp;
			}

	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	return 0;
}