// ÀºøºÃ‚ 2-2
#include <iostream>
using namespace std;

	// √∞≈›≈≈–Ú
void BubbleSort(int * A, int len);

	// —°‘Ò≈≈–Ú
void SelectionSort(int * A, int len);

int main(void)
{
	const int Size = 100;
	int A[Size];
	int Ar[Size];
	for (int i = 0; i < Size; i++)
		Ar[i] = A[i] = rand() % 100;

	BubbleSort(A, Size);
	for (int i = 0; i < Size; i++)
		cout << A[i] << " ";
	cout << endl;
	SelectionSort(Ar, Size);
	for (int i = 0; i < Size; i++)
		cout << Ar[i] << " ";

	return 0;
}

void BubbleSort(int * A, int len)
{
	for (int i = 0; i < len; i++)
		for (int j = len - 1; j > i; j--)
			if (A[j] > A[j - 1])
			{
				int temp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = temp;
			}
}

void SelectionSort(int * A, int len)
{
	for (int i = 0; i < len; i++)
		for (int j = i + 1; j < len; j++)
			if (A[j] < A[i])
			{
				int temp = A[j];
				A[j] = A[i];
				A[i] = temp;
			}
}