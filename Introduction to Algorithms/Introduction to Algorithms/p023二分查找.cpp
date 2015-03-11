// 习题2.3-5	二分查找(Binary Search)
// 二分查找的时间复杂度是: lgn
#include <iostream>
using namespace std;
#define 递归实现	
//#define 迭代实现

#ifdef 递归实现
int BinarySearch(int * A, int L, int R, int V);

int main(void)
{
	int A[] = {1, 3, 5, 6, 7, 8, 19};
	int N = sizeof A / sizeof *A;
	int L = 0, R = N;
	int V = 7;
	int M = BinarySearch(A, L, R, V);
	if (M == -1)
		cout << "A数组中不存在" << V << endl;
	else
		cout << V << "在数组中的A[" << M << "]\n";
}

int BinarySearch(int * A, int L, int R, int V)
{
	if (L == R-1 && A[L] != V)	// 如果到了L R挨着, 此时M = (L + R) / 2 = L; 若A[L] != V, 则下次迭代L R的值不变, 会陷入死迭代, 所以应该退出
	{
		V = -1;
		return V;
	}
	int M = (L + R) / 2;
	if (V < A[M])
		return BinarySearch(A, L, M, V);
	else if (V > A[M])
		return BinarySearch(A, M, R, V);
	else	// V == A[M]
		return M;
}
#elif defined 迭代实现

int main()
{
	int V = 10;
	int A[] = {1, 3, 6, 8, 9};
	int N = sizeof A / sizeof *A;

	int M;
	for (int L = 0, R = N;;)
	{
		M = (L + R) / 2;
		if (L == M && A[M] != V)	// 不存在V
		{
			M = -1;
			break;
		}
		if (A[M] == V)
			break;
		else if (A[M] > V)
			R = M;
		else if (A[M] <= V)
			L = M;
	}
	if (M == -1)
		cout << "A数组中不存在" << V << endl;
	else
		cout << V << "在数组中的A[" << M << "]\n";

}

#endif