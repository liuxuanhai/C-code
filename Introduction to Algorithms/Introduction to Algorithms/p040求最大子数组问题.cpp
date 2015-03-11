// 求一个数组中的最大数组
// 140716 不好的地方	1. SubarrayFlagTag FindCrossingSubarray(int * A, int L, int R)等地方R不是右界而是右界后一位, 造成逻辑混乱
//						2. for (int i = M - 1; i >= L; i--) 	#1  这里用的是M - 1 来表示左半部分, 与书中不符, 也与通常逻辑不符, 最好改成 [L, M]左 [M + 1, R]右
#include <iostream>
using namespace std;
int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
int N	= sizeof A / sizeof *A;
#define 暴力方法

#ifdef 暴力方法

int main(void)
{
		// 暴力方法

	int L = 0, R = 1, MaxTemp = 0;
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
		{
			int temp = 0;
			for (int m = i; m <= j; m++)
				temp += A[m];
			if (temp > MaxTemp)
			{
				MaxTemp = temp;
				L = i;
				R = j;
			}
		}

	cout << "[" << L << "," << R << "]\n";
}

#else

	// 使用分治策略

		// 标记数组位置的数据结构

struct SubarrayFlagTag
{
	int L;		// 最小数组左索引
	int R;		// 右索引
	int MaxVal;	// 值
};

		// 最大数组包含中点的情况

SubarrayFlagTag FindCrossingSubarray(int * A, int L, int R)
{
	int M = (L + R) / 2;	// 中点索引

			// CrossingSubarray的左半部分计算

	int LMaxSum	= -111;	// 不标准的使用了一个-111
	int temp	= 0;
	int LTemp;
	for (int i = M - 1; i >= L; i--)	// # 1 140716
	{
		temp += A[i];
		if (temp > LMaxSum)
		{
			LMaxSum	= temp;
			LTemp	= i;
		}
	}

			// 右半部分

	int RMaxSum	= -111;
	int RTemp;	
	temp = 0;
	for (int i = M; i < R; i++)
	{
		temp += A[i];
		if (temp > RMaxSum)
		{
			RMaxSum	= temp;
			RTemp	= i + 1;	// 这里别忘了加一
		}
	}

	SubarrayFlagTag tempSubarray = {LTemp, RTemp, LMaxSum + RMaxSum};
	return tempSubarray;
}

SubarrayFlagTag FindSubarray(int * A, int L, int R)
{
	
	if (L == R - 1)
	{
		SubarrayFlagTag tempSubarray = {L, R, A[L]};
		return tempSubarray;
	}
	else
	{
		int M = (L + R) / 2;
		SubarrayFlagTag LSubarray = FindSubarray(A, L, M);
		SubarrayFlagTag RSubarray = FindSubarray(A, M, R);
		SubarrayFlagTag MSubarray = FindCrossingSubarray(A, L, R);
		if (LSubarray.MaxVal >= RSubarray.MaxVal && LSubarray.MaxVal >= MSubarray.MaxVal)
			return LSubarray;
		else if (RSubarray.MaxVal >= LSubarray.MaxVal && RSubarray.MaxVal >= MSubarray.MaxVal)
			return RSubarray;
		else
			return MSubarray;
	}
}

int main(void)
{
	SubarrayFlagTag Subarray = FindSubarray(A, 0, N);

	cout << "[" << Subarray.L << ", " << Subarray.R - 1 << "]\n";

	return 0;
}

#endif