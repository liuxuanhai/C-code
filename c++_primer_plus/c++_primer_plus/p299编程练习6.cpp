// 编程练习 8.8 (6)
#include <iostream>
#include <cstring>
template<class T> T maxn(T ar[], int n);
template<> char * maxn<char *>(char * ar[], int n); // 具体化必须有上面这个模板作支持

int main()
{
	using namespace std;
	int ar[6] = {1, 2, 3, 4, 5, 6};
	double arr[4] = {1.1, 2.2, 3.3, 4.4};
	char * arrr[5] = {"daxiong", "daxionggg", "didiaodedaxiong", "heshixiong", "daxionggege"};

	cout << maxn(ar, 6) << endl;
	cout << maxn(arr, 4) << endl;
	cout << maxn(arrr, 5) << endl;

	return 0;
}

template<class T> T maxn(T ar[], int n)
{
	T temp = ar[0];
	for (int i = 1; i < n; i++)
		if (ar[i] > temp)
			return temp = ar[i];
}

template<> char * maxn(char * ar[], int n)
{
	int temp = 0;
	for (int i = 1; i < n; i++)
		if (strlen(ar[temp]) < strlen(ar[i]))
			temp = i;
	return ar[temp];
}