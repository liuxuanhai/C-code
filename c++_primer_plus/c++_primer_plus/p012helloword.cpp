// 程序清单 2.1
// 输出一条信息
#include <iostream>
int main ()
{
	using namespace std;
	cout << "Come up and C++ me some time.";  // 可以使用std名称空间中定义的名称而不必使用std::前缀
	  // '<<'插入运算符, 他将右侧的信息插入到流中
	cout << endl;
	cout << "You won't regret it!" << endl;

	return 0;
}