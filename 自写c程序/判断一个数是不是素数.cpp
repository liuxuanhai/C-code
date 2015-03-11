// 求一个数是不是素数
// 注意: scanf()在扫描到遇到的第一个空格的时候停止, 所以他只能读取一个单词, 如果想要读取更多使用gets();
#include <stdio.h>

int prime (int);

int main (void)
{
	int n;

	printf ("请输入一个数:\n");
	while(scanf ("%d", &n))
	{
		if(0 == prime(n))
			printf ("%d不是素数.\n", n);
		else
			printf ("%d是素数.\n", n);
	}
	return 0;
}

int prime (int n)
{
	if (1 == n)
		return 0;
	
	for (int i = 2; i * i <= n; i++)
		if (0 == n % i)
			return 0;
	
	return 1;
}