// 习题2.3-6 将2.1的插入算法的5-7行的查找改成二分查找
// 时间复杂度是n^2
#include <iostream>
using namespace std;

void InsertionSort(int * A, int len);
	// 如果v在给定数组中, 返回此值偏移量, 如果v比任何元素都大, 返回数组元素最后一个偏移量+1, 如果v比任何元素都小, 返回的不是第一个元素的偏移量-1, 这是为了插入的方便, 是一种妥协
int  BinarySearch(int * Ar, int p, int r, int v);	// p是开始元素偏移量, !r是Ar中元素个数!

int main(void)
{
	const int SIZE = 100;
	int A[SIZE];
	int N	= sizeof A / sizeof *A;
	for (int i = 0; i < N; i++)
		A[i] = rand() % 100;
	InsertionSort(A, N);
	for (int i = 0; i < N; i++)
		cout << A[i] << " ";

	return 0;
}

void InsertionSort(int * A, int len)
{
	for (int i = 1, r = 0; i < len; i++)
	{
		int j = BinarySearch(A, r, i, A[i]);	// 二分寻找A[r, i-1]中A[i]合适的位置

			// 将A[i]放在数组合适的位置, 将数组中相应的元素后移
		int temp = A[i];						// 虽然查找是clgn, 但是数组中的位置移动还是cn, 所以如果是链表的话会有效率上的极大提高, 对于这个, 时间复杂度不变, 反而常数增大了...
		for (int m = i; m > j; m--)
			A[m] = A[m-1];
		A[j] = temp;
	}
}

int BinarySearch(int * A, int p, int r, int v)
{
	if (p >= r)
	{
		cout << "Error: Wrong parameters of BinarySearch function, should be p <= r!\n";
		exit(EXIT_FAILURE);
	}
	if (p + 1 == r)						// 此时查找的状态是p + 1 = q, 理解的思路是, p是数组元素如0, r是元素个数如1, 然后此时进行到了只有一个元素的状态
	{
		if (v <= A[p])					// 如果v在A[p]的左边, 或者v == A[p]
			return p;
		else if (v > A[p])				// 如果v在A[p]的右边
			return r;
	}
	int m = (p + r) / 2;
	if (A[m] == v)	// 在某次二分上正好找到了一样大的值
		return m;
	else if (v > A[m])			// 上述情况都不存在, 则一直递归下去
		return BinarySearch(A, m, r, v);
	else
		return BinarySearch(A, p, m, v);
}