#include <iostream>
int main()
{
	using namespace std;
	int a[10];
	// a++;  // 报错, 因为他是const int *
	int *const(& b) = a;  // 由于a是不可修改的数组名字, 如果直接引用的话应该声明他是一个指向不可修改的指针的引用  const int * a;(int是不可修改的, int const a = 2跟const int a = 2一样) int * const a;(int * 是不可修改的)
		// 对常量指针的引用
	int * bb = a;
	int c;
	int & cc = c;  // 引用必须初始化, 初始化以后就不能修改
	int * const pr = &c;  // 其实cc就是*pr
	

	return 0;
}