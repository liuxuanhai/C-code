//找出组合中的最大数
#include <stdio.h>

int main (void)
{	int num, num1, num2, temp;

	printf ("请输入三个数字(0~9):\n");
	while(scanf("%1d %1d %1d", &num, &num1, &num2) == 3)
	{
		if (num > num1)
		{
			temp = num;
			num = num1;
			num1 = temp;
		}
		if (num1 > num2)
		{
			temp = num2;
			num2 = num1;
			num1 = temp;
		}
		if (num > num1)
		{
			temp = num;
			num = num1;
			num1 = temp;
		}
		printf ("最大数为:%d%d%d\n", num2, num1, num);
		printf ("最小数为:%d%d%d\n", num, num1, num2);
	}
	return 0;
}
