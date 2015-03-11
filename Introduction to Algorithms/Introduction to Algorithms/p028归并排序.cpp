#include <iostream>
#include <cstdlib>
#define YA -1

	// 将两个已经排好序的序列组合成一个排好序的序列
void MERGE(int * A, int p, int q, int r);	// A[p, q], A[q+1, r] rs是能够取到的
void MERGE_SORT(int * A, int p, int r);

int main(void)
{
	const int SIZE = 1023;
	int A[SIZE];
	for (int i = 0; i < SIZE; i++)
		A[i] = rand() % 100;

	std::cout << "排序前: \n";
	for (int i = 0; i < SIZE; i++)
		std::cout << A[i] << ' ';

	std::cout << "\n排序中... \n";
	MERGE_SORT(A, 0, SIZE-1);

	std::cout << "\n排序后: \n";
	for (int i = 0; i < SIZE; i++)
		std::cout << A[i] << ' ';

	std::cout << std::endl;
	return 0;
}

void MERGE(int * A, int p, int q, int r)
{

		// 给树杈分配内存

	int n1 = q - p + 1;
	int n2 = r - q;
	int *L = new int[n1 + 1];	// + 1 放置哑元素
	int *R = new int[n2 + 1];

		// 将数组A中未排序的部分分成两部分分别保存到两个树杈中

	for (int i = 0; i < n1; i++)
		L[i] = A[p + i];
	for (int i = 0; i < n2; i++)
		R[i] = A[q + 1 + i];
	
	L[n1] = YA;	// 哑元素标识序列的结尾
	R[n2] = YA;

		//	对两个序列进行排序合并, 将排好序的序列放在A中

		// 比较的结果是A[p, r]中的所有元素都更新值了, 所以比较了r-p+1次, 所以这里出现YA == L[i] && YA == R[j]的时候正好跳出循环才对, 所以k++放在了for中而不是每次使用A[k++] = ..
	for (int k = p, i = 0, j = 0; k <= r; k++)
	{
		if ((YA == R[j] && YA != L[i]) || // 如果有一个序列取完, 到了哑元素
			(L[i] <= R[j] && YA != L[i] && YA != R[j]))	// 如果两个序列都没有取完, 则应该保证比较元素不是哑元素
			A[k] = L[i++];
		else if ((YA == L[i] && YA != R[j]) || (R[j] < L[i] && YA != L[i] && YA != R[j]))
			A[k] = R[j++];
	}
}

void MERGE_SORT(int * A, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;		
		MERGE_SORT(A, p, q);
		MERGE_SORT(A, q+1, r);
		MERGE(A, p, q, r);
	}
}