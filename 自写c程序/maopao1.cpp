//找出组合中的最大数     // !!!!!!!!!通过定义全局域解决了问题!!!!!!!!!
#include <stdio.h>

int max,min;

int maopao (int n1, int n2);  //冒泡排序原型
int main (void)
{	int num, num1, num2;

	printf ("请输入三个数字(0~9):\n");
	while(scanf("%1d %1d %1d", &num, &num1, &num2) == 3)
	{
		maopao (num, num1);
		num = min;
		num1 = max;
		maopao (num1, num2);
		num1 = min;
		num2 = max;
		maopao (num, num1);
        num = min;
		num1 = max;
		printf ("最大数为:%d%d%d\n", num2, num1, num);
		printf ("最小数为:%d%d%d\n", num, num1, num2);
	}
	return 0;
}
int maopao (int n1, int n2)  //定义冒泡函数
{
	int temp;

	if (n1 > n2)
		{
			temp = n2;
			n2 = n1;
			n1 = temp;
		}
	max = n2; 
	min = n1;
	return n1;
}