// 编程练习 5
// 一个猜数字程序
#include <stdio.h>
#include <ctype.h>
#define SIZE 50
int main(void)
{
	int middle = SIZE;
	int left = 0, right = SIZE * 2;
	int flag = 0;
	int temp;
	char ch;

	printf("%d?<big/little/right>\n", middle);
	while(EOF != (ch = getchar()))
	{
		if(ch != '\n')
			while('\n' != getchar())
				continue;
		ch = tolower(ch);
		if(ch == 'l' && flag == 0)
		{
			left = middle;
			middle = right;
			right += SIZE;
			flag = 3;
		}
		else if(ch == 'l')
		{
			left = middle;
			middle = middle + (int)((right - middle) / 2);
		}
		if(ch == 'b')
		{
			right = middle;
			middle = middle - (int)((middle - left) / 2);
		}
		if(ch == 'r')
			break;
		if(ch != 'l' && ch != 'b' && ch != 'r')
		{
			puts("输入错误, 请重新输入!");
			continue;
		}
		if(flag == 0)
			flag = 1; // 只能在第一次循环的时候输入的是'l'对应哪个分支
		else if(flag == 3)
			flag = 0;
		printf("left: %d middle: %d right: %d\n", left, middle, right);
		printf("%d?<big/little/right>\n", middle);
	}

	return 0;
}