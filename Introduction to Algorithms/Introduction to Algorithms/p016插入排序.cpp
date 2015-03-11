#include <iostream>
using namespace std;

int main(void)
{
	int A[] = {5, 2, 4, 6, 1, 3};

		// 插入法

	for (int j = 1; j < sizeof A / sizeof *A; j++)	// n
	{
		int key = A[j];								// n - 1
		int i = j - 1;								// n - 1
		while (i >= 0 && A[i] > key)				// 
		{
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}

		// 选择法

	for (int i = 0; i < (sizeof A / sizeof *A - 1); i++)
		for (int j = i + 1; j < sizeof A / sizeof *A; j++)
			if (A[i] > A[j])
			{
				int temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}

	for (int i = 0; i < sizeof A / sizeof *A; i++)
		cout << A[i] << endl;

	return 0;
}