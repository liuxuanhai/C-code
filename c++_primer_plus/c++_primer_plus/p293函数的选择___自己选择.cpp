// 程序清单 8.15
#include <iostream>

auto lesser (int a, int b) -> int          // #2
	// 将返回类型移到参数声明后面  -> int 被称为后置返回类型
	// auto是一个占位符, 表示后置返回类型提供的类型
{
	a = a < 0 ? -a : a;
	b = b < 0 ? -b : b;
	return a < b ? a : b;
}
template<class T> T lesser(T a, T b) // #1
{
	return a < b ? a : b;
}

int main()
{
	using namespace std;
	int m = 20;
	int n = -30;
	double x = 15.5;
	double y = 25.9;

	cout << lesser(m, n) << endl;      // use #2
	cout << lesser(x, y) << endl;      // use #1
	cout << lesser<>(m, n) << endl;    // use #1
		// <>指出编译器应该选择模板函数而不是非模板函数
	cout << lesser<int>(x, y) << endl; // use #1
		// 这条语句要求进行显示实例化(使用int代替T), 将使用显示实例化得到的函数, x和y被强制转换为int, 该函数返回一个int

	return 0;
}