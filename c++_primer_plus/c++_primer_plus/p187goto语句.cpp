// 自己总结
#include <iostream>
int main()
{
	using namespace std;
	int a = 0, b = 0;
a: std::cout << a << endl; // 第一次执行到这里的时候不跳过
	cout << b << endl;
	b++;
	a = 2;
	while ( b < 3 )
		goto a;

	return 0;
}