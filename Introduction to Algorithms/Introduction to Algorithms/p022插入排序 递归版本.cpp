// 练习 2.3-4
// 先递归排序A[n]中的A[n-1]部分, 然后将第n个插入进去
#include <iostream>
using namespace std;

	// 负责递归的函数
void InsertSort(int * A, int len);
	// 负责插入的函数
void Insert(int * A, int len);	// len是要插入的项, 0 ~ len-1是已经排好序的

int main(void)
{
	const int SIZE = 1000;
	int A[SIZE];

	for (int i = 0; i < SIZE; i++)
		A[i] = rand() % 1000;
	for (int i = 0; i < SIZE; i++)
		cout << A[i] << " ";
	cout << endl;

	InsertSort(A, SIZE);

	cout <<endl;
	for (int i = 0; i < SIZE; i++)
		cout << A[i] << " ";

	return 0;
}

void InsertSort(int * A, int len)
{
	if (len <= 1)	// 一直递归到只剩一个元素的时候退出
		return;
	InsertSort(A, len-1);
	Insert(A, len);
}

void Insert(int * A, int len)
{
	for (int i = len - 2, temp, j = len - 1; i >= 0; i--, j--)
	{
		if (A[j] >= A[i])
			break;
		temp = A[j];
		A[j] = A[i];
		A[i] = temp;
	}
}