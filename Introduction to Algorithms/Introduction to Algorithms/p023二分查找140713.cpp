// 练习2.3-5 二分查找
#include <iostream>

#ifdef DiGui
int binarySearch(const int A[], int L, int R, int V)
{
	if (L > R)
		return -1;
	int M = (L + R) / 2;
	if (A[M] == V)
		return M;
	else if (A[M] > V)
		return binarySearch(A, L, M - 1, V);
	else
		return binarySearch(A, M + 1, R, V);
}

#else

int binarySearch(const int A[], int L, int R, int V)
{
	while (L <= R)
	{
		int M = (L + R) / 2;
		if (A[M] == V)
			return M;
		else if (A[M] > V)
			R = M - 1;
		else
			L = M + 1;
	}
	return -1;
}
#endif

int main(void)
{
	int A[] = {1, 3, 5, 7, 9};
	int N	= sizeof A / sizeof *A;
	int key, temp;
	for (int i = 0; i < 10; i++)
	{
		key = i;
		temp = binarySearch(A, 0, N - 1, key);
		if (temp != -1)
			std::cout << "A[" << temp << "] = " << key << std::endl;
		else
			std::cout << "A数组中不存在" << key << std::endl;
	}
}
