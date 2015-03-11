// 习题 2.3-2
#include <iostream>
using namespace std;

	// 将两个排好的元素序列合并成一个排好序的序列
void Merge(int * A, int front, int mid, int rear);

	// 排序函数, 将一个数组排好序, 除了内嵌的Merge, 它主要负责拆分, 一直拆分到只有一个元素, 这就成了排好序的了
void MergeSort(int * A, int f, int l);

int main(void)
{
	const int SIZE = 1000;
	int A[SIZE];

	for (int i = 0; i < SIZE; i++)
		A[i] = rand() % 1000;
	for (int i = 0; i < SIZE; i++)
		cout << A[i] << " ";
	cout << endl;

	MergeSort(A, 0, SIZE - 1);

	cout <<endl;
	for (int i = 0; i < SIZE; i++)
		cout << A[i] << " ";

	return 0;
}

void MergeSort(int * A, int f, int l)
{
	if (f >= l)	// 如果少于或等于一个元素, 就不用分了, 直接开始排序
		return;
	int m = (f + l) / 2;	// (l - f + 1) / 2; !!!!!!!!!!!!!! 这两种写法比较 !!!!!!!!!!!!!!!!!!!
	MergeSort(A, f, m);
	MergeSort(A, m + 1, l);
	Merge(A, f, m, l);
}

void Merge(int * A, int f, int m, int l)
{
		// 分内存
	int Num1	= m - f + 1;	// 计算左杈元素个数
	int Num2	= l - m;		// 计算右杈元素个数
	int * L		= new int[Num1];// 不使用哑元素, 不用给他分配内存
	int * R		= new int[Num2];

		// 赋值
	for (int i = 0; i < Num1; i++)
		L[i] = A[f + i];
	for (int i = 0; i < Num2; i++)
		R[i] = A[m + 1 + i];

		// 合并
	for (int iL = 0, iR = 0, iA = f; ; )
	{
		if (iL >= Num1)	// 如果左杈元素取完了, 直接将右杈赋给A
		{
			for (int i = iR; i < Num2; i++)
				A[iA++] = R[i];
			break;
		}
		if (iR >= Num2)	// 如果右杈元素取完了
		{
			for (int i = iL; i < Num1; i++)
				A[iA++] = L[i];
			break;
		}
		if (L[iL] < R[iR])
			A[iA++] = L[iL++];
		else
			A[iA++] = R[iR++];
	}
}