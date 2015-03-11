// 程序清单 5.5
// 改程序允许用户修改程序执行的次数, 还有i的递增梯度
#include <iostream>
int main()
{
	using std::cout; // 一个使用声明
	using std::cin;  // 这种的是using声明而不是using namespace std编译指令
	using std::endl;
	cout << "Enter an integer: \n";
	int by;
	cin >> by;
	cout << "Counting by " << by << "s:\n";
	for (int i = 0; i < 100; i = i + by)
		cout << i << endl;

	return 0;
}