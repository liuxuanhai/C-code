// p119 例 5-10 汉诺塔与递归
#include <stdio.h>

void moveDisk (int, char, char, char);      // disk圆盘

int main (void)
{
	int n;

	printf ("输入要移动的盘子数:\n");
	scanf ("%d", &n);

	moveDisk (n, 'A', 'B', 'C');

	return 0;
}

void moveDisk (int diskNum, char sourcePole, char midPole, char targetPole)
{
	if (1 == diskNum)
		printf ("%c -> %c\n", sourcePole, targetPole);
	else
	{
		// 将n-1个盘子从A针移到B针,借助C针
		moveDisk (diskNum - 1, sourcePole, targetPole, midPole);

		// 将A针上的盘子移到C针
		printf ("%c -> %c\n", sourcePole, targetPole);

		// 将n-1个盘子从B针移到C针,借助A针
		moveDisk (diskNum - 1, midPole, sourcePole, targetPole);
	
	}

}