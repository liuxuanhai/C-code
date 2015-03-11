// 输入一个整数,程序给出小于或等于该数的所有素数
#include <stdio.h>
int main (void)
{
	int input, output, index, i, issushu;               //这里没有直接初始issushu为1 因为如果初始化为1 那么输入2将直接输出2 它将保证输出每个数之前都是经过了判断的

	printf ("给我一个整数,我还给你小于或等于这个数的所有素数(#是结束程序):\n");
	while (1 == scanf ("%d", &input))
	{
		if (input <= 2)
		{
			printf ("请输入比2大的数!\n");
			continue;
		}
		for (index = 3; index <= input; index++)        // 从2开始穷举到输入的整数
		{
			for (i = 2; i < index; i++)            // 开始寻找穷举数的约数,判断是不是质数
			{
				issushu = 1;                            // 如果放在for()内的初始化里那么相当于放在while上的初始化,即使for一次没执行也将为1
				if (0 == (index % i))                                              //而且一旦改为0接下来的循环无法初始化为1
				{
					issushu = 0;
					break;                              // 如果break位于嵌套循环内 它将只影响内层循环
				}
			}
			if (1 == issushu)
			{
				printf ("%4d", index);
			}
		}
		printf ("\n");
	}
	return 0;
}