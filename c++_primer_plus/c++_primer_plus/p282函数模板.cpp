// 程序清单 8.11
#include <iostream>
template <typename T> // template 模板 // 可以用class代替typename
void Swap(T &a, T &b);
// 模板不会创建任何函数, 只是告诉编译器如何定义函数, 需要交换int函数的时候, 编译器将会按模板模式创建这样的函数, 并用int代替T
// 函数模板不能缩短可执行程序, 最终仍将有两个独立的函数定义, 就像是手工方式定义了这些函数一样, 最终代码不包含任何模板

int main()
{
	using namespace std;
	int i = 10;
	int j = 20;
	cout << "i, j = " << i << ", " << j << ".\n";
	cout << "Using compiler-generated int swapper:\n";
	Swap(i, j);
	cout << "Now j, j = " << i << ", " << j << ".\n";

	double x = 24.5;
	double y = 81.7;
	cout << "x, y = " << x << ", " << y << ".\n";
	cout << "Using compiler-generated double swapper:\n";
	Swap(x, y);
	cout << "Now x, y = " << x << ", " << y << ".\n";

	return 0;
}

template <typename T>
void Swap(T &a, T &b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}