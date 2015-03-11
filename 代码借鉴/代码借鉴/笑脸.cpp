// 一个笑脸在控制台内碰撞
#include <windows.h>
#include <stdio.h>
void coord(int x, int y)
{
	for (; y; y--)
		printf("\n");
	for (; x; x--)
		printf(" ");
}

int main(void)
{
	int x = 20;
	int y = 0;
	int xv = 1;
	int yv = 1;

	while (1)
	{
		system("cls");
		x += xv;
		y += yv;
		if (x == 80 || x == 0)
			xv *= -1;
		if (y == 20 || y == 0)
			yv *= -1;
		coord(x, y);
		printf("...%c...", 2);
	}

	return 0;
}