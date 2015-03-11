#include <stdio.h>
#define IABS(x) ( (x) >= 0 ? (x) : -(x) ) //定义一个计算绝对值的宏
int main(void)
{
	for (int x = -5; x <= 5; x++)
		if (IABS(x) <= 3)
			putchar('*');
		else
			putchar(' ');
	putchar('\n');
	
	putchar('\n');

	for (int x = 0; x <= 5; x++)
	{
		for (int y = 0; y <= x; y++)
			putchar('*');
		putchar('\n');
	}

	putchar('\n');

	for (int x = 0; x <= 5; x++)
	{
		for (int y = -5; y <= 5; y++)
			if (IABS(y) <= x)
				putchar('*');
			else
				putchar(' ');
		putchar('\n');
	}

	putchar('\n');

	for (int x = -5; x <= 5; x++)
	{
		for (int y = -5; y <= 5; y++)
			if (IABS(y) <= IABS(x))
				putchar('*');
			else
				putchar(' ');
		putchar('\n');
	}

	putchar('\n');
	
	for (int x = -5; x <= 5; x++)
	{
		for (int y = -5; y <= 5; y++)
			if (IABS(y) <= IABS(x))
				putchar(' ');
			else
				putchar('*');
		putchar('\n');
	}

	putchar('\n');

	for (int x = -5; x <= 5; x++)
	{
		for (int y = -5; y <= 5; y++)
			if (IABS(y) + IABS(x) <= 5)
				putchar('*');
			else
				putchar(' ');
		putchar('\n');
	}

	putchar('\n');

	for (int x = -5; x <= 5; x++)
	{
		for (int y = -5; y <= 5; y++)
			if (IABS(y) + IABS(x) <= 5)
				putchar(' ');
			else
				putchar('*');
		putchar('\n');
	}

	putchar('\n');

	return 0;
}