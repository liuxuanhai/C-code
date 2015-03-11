#include <iostream>
#include <ctime>
using namespace std;
#define 暴力解法
#ifdef 暴力解法

void maxArray(const int * A, int N)
{
	int L = 0, R = 1;
	int max = A[0] + A[1];
	for (int i = 0; i < N; i++)
	{
		int temp = A[i];
		for (int j = i + 1; j < N; j++)
		{
			if ((temp += A[j]) > max)
			{
				max = temp;
				L = i;
				R = j;
			}
		}
	}
	cout << L + 1 << " " << R + 1 << endl;
}

#else

struct maxTag
{
	int L;
	int R;
	int max;
};

maxTag maxMidArray(const int * A, int L, int R)
{
	int M = (L + R) / 2;

	// find LMax
	maxTag LMax = {M, M, A[M]}; 
	for (int i = M, tempMax = 0; i >= L; i--)
	{
		tempMax += A[i];
		if (tempMax > LMax.max)
		{
			LMax.max = tempMax;
			LMax.L = i;
		}
	}

	//if (L == R)	// 如果只有一个数, 那么LMax等于这个数, RMax不存在	// 这种情况根本不存在, 因为在L == R的时候, 求中最大数组函数不会执行
	//	return LMax;

	// find RMax
	maxTag RMax = {M + 1, M + 1, A[M + 1]};
	for (int i = M + 1, tempMax = 0; i <= R; i++)
	{
		tempMax += A[i];
		if (tempMax > RMax.max)
		{
			RMax.max = tempMax;
			RMax.R = i;
		}
	}

	//// 比较返回	// 这里用不着比较返回, 因为单独LMax或RMax而非中数组的话, 已经求出了他们的最大值, 这里的LMax只是求出最大值的一个子集情况, 这里只需 返回中数组的最大值然后在另一个函数中在于他们比较就行了
	maxTag T = {LMax.L, RMax.R, LMax.max + RMax.max};
	//if (LMax.max > RMax.max && LMax.max > T.max)
	//	return LMax;
	//else if (RMax.max > LMax.max && RMax.max > T.max)
	//	return RMax;
	//else
		return T;
}

maxTag maxArray(const int * A, int L, int R)
{
	if (L == R)
	{
		maxTag temp = {L, R, A[L]};
		return temp;
	}
	maxTag data1, data2, data3;
	int M = (L + R) / 2;
	data1 = maxArray(A, L, M);
	data2 = maxArray(A, M + 1, R);
	/*if (data1.R + 1 == data2.L)
	{
		maxTag temp = {data1.L, data2.R, data1.max + data2.max};
		data3 = temp;
	}
	else
		data3 = data2;*/	// 不对的方法, 很多对都没有涉及到

	data3 = maxMidArray(A, L, R);

	if (data1.max < data2.max && data2.max > data3.max)
		return data2;
	else if (data1.max > data2.max && data1.max > data3.max)
		return data1;
	else
		return data3;
}
#endif


#include "算法计时.h"
//#define 书中例子
int main(void)
{
	CLOCKSTART;
#ifdef 书中例子
	int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int N	= sizeof A / sizeof *A;
#else 
	const int N = 50000;	// 5W以下的数
	int A[N];
	srand(1);
	for (int i = 0; i < N; i++)
		A[i] = rand() % N - N / 2;
#endif
#ifdef 暴力解法
	maxArray(A, N);
#else
	maxTag temp = maxArray(A, 0, N - 1);
	cout << temp.L + 1 << " " << temp.R + 1 << endl;
#endif
	SHOWTIME;
}