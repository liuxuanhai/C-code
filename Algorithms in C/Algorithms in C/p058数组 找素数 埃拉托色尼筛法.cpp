// 素数: 最小为2, 大于1, 只能被1和本身整除
// 合数: 最小为4, 大于1, 除了素数剩下的
// 0, 1: 既不是素数也不是合数;
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define N	1000000000  // 当N为10W的时候, 自己写的等光标闪烁6下出结果, 厄拉多塞筛一下闪烁都不用
#define N 100
//#define	埃拉托色尼筛法_动态内存
//#define 自己写的
#define windows程序设计p934
int main(void)
{
#if defined 埃拉托色尼筛法

	int i, j;
	int a[N];	// 当数量为100w的时候, 保存这些数据需要30M, 好像栈中不能保存这么多

	for (i = 2; i < N; i++)
		a[i] = 1;
	for (i = 2; i < N; i++)
		if (a[i])
			for (j = i; (long long)j * i < N; j++) // 如果不是longlong的话, i * j在计算10w级的时候会出现数据溢出
				a[i*j] = 0;

	int Num = 0;
	for (i = 2; i < N; i++)
		if (a[i])
		{
			printf("%4d ", i);
			Num++;
		}
	printf("\n共%d个素数", Num);

#elif defined 埃拉托色尼筛法_动态内存
	int i, j;
	//int a[N];	// 当数量为100w的时候, 保存这些数据需要30G;
	int * a;
	if (!(a = (int *)malloc(sizeof (int) * N)))
	{
		printf("没有那么多内存!\n");
		return 0;
	}

	for (i = 2; i < N; i++)
		a[i] = 1;
	for (i = 2; (long long)i * i < N; i++)	// 这里把i < N改成(long long)i * i < N;对1亿以内的计算几乎没影响, 都是光标闪烁5下
		if (a[i])
			for (j = i; (long long)j * i < N; j++) // 如果不是longlong的话, i * j在计算10w级的时候会出现数据溢出
				a[i*j] = 0;

	int Num = 0;
	for (i = 2; i < N; i++)
		if (a[i])
		{
			printf("%4d ", i);
			Num++;
		}
	printf("\n共%d个素数", Num);


#elif defined 自己写的	// 自己写的
	
	int * ar;
	if (!(ar = (int *)malloc(sizeof (int) * N)))
	{
		printf("没有那么多内存!\n");
		return 0;
	}

	for (int i = 0; i < N; i++)
		ar[i] = 0;

	int j;
	for (int i = 2; i < N; i++)
	{
		for (j = 2; j < i / 2; j++)	// 优化 1: 这里判断素数约数的范围只用检查到i/2即可
			if (i % j == 0)
				break;
		if (j >= i / 2)	// 优化 2: 这里也就将i改成了i/2, 但是==改成了>=, 为的是把2, 3包含进去
			ar[i] = 1;
		ar[4] = 0;		// 优化 3: 但是这样会把4包含进去, 所以这条语句用来防止这种情况
	}
	int Num = 0;
	for (int i = 0; i < N; i++)
		if (ar[i] == 1)
		{
			printf ("%d ", i);
			Num++;
		}
	printf("\n共%d个素数\n", Num);

#elif defined windows程序设计p934
	int * ar;
	if (!(ar = (int *)malloc(sizeof (int) * N)))
	{
		printf("没有那么多内存!\n");
		return 0;
	}
	for (int i = 0; i < N; i++)
		ar[i] = 0;

	int iNum = 1, iSqrt, i;
	for (int ii = 0; ii < 100; ii++)
	{
		do
		{ 
			if (++iNum < 0) 
				iNum = 0 ; 
			iSqrt = (int) sqrt (double(iNum)) ; 

			for (i = 2 ; i <= iSqrt ; i++) 
				if (iNum % i == 0) 
			break ; 
		} while (i <= iSqrt) ; 
		printf("%d ", iNum);
	}

#endif
	return 0;
}