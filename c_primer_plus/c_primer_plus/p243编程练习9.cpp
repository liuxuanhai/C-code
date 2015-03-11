// 编程练习 9.11 (9)
#include <stdio.h>
float power(float a, int b);
int main()
{
	float a;
	int b;
	puts("float a: ");
	while (scanf("%f", &a) == 1)
	{
		puts("int b: ");
		scanf("%d", &b);
		printf("%g\n", power(a,b));
		puts("float a: ");
	}

	return 0;
}

float power(float a, int b)
{
	float sum = 1;
	if (b > 0)
		for (int i = 0; i < b; i++)
			sum *= a;
	else if (b < 0)
		//for (int i = 0; i < -b; i++)
		//	sum *= (float)1 / a;
			sum *= 1 / power(a,-b);   // 这样调用显然比上面那种方法简单
	else if (b = 0)
		sum = b;

	return sum;
}