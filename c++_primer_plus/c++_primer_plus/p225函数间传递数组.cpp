// 自己总结
#include <iostream>
using namespace std;

void Array1(int (*)[4], int);
//void Array2(int ***, int, int);

int main()
{
	int ar[3][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6}
	};
	Array1(ar, 3);
	//int (*ptr)[4] = ar;
	//Array2(&ptr, 3, 4);
}

void Array1(int ar[][4], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << ar[i][j];
		cout << endl;
	}
}