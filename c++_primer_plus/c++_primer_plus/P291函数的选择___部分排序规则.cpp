// 程序清单 8.14
// 重载解析将会寻找最匹配的函数
#include <iostream>

template <typename T> void ShowArray(T array[], int n); // template A

template <typename T> void ShowArray(T * array[], int n);// template B

struct debts
{
	char name[50];
	double amount;
};

int main()
{
	using namespace std;
	int things[6] = {13, 31, 103, 301, 310, 130};
	struct debts mr_E[3] =
	{
		{"Ima Wolfe", 2400.0},
		{"Ura Foxe", 1300.0},
		{"Iby Stout", 1800.0}
	};
	double * pd[3];

	for (int i = 0; i < 3; i++)
		pd[i] = &mr_E[i].amount;

	cout << "Listing Mr. E's counts of things :\n";
	ShowArray(things, 6); // use template A
	cout << "Listing Mr. E's debts:\n";
	ShowArray(pd, 3);     // use template B
						 // 如果没有templateb的话, 他会使用template A 那时候T就会被转换成double *而不是double

	return 0;
}

template <typename T> void ShowArray(T arr[], int n)
{
	using namespace std;
	cout << "template A\n";
	for (int i = 0; i < n; i++)
		cout << arr[i] << ' ';
	cout << endl;
}

template <typename T> void ShowArray(T * arr[], int n)
{
	using namespace std;
	cout << "template B\n";
	for (int i = 0; i < n; i++)
		cout << *arr[i] << ' ';
	cout << endl;
}