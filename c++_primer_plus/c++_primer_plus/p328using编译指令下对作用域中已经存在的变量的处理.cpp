#include <iostream>
using namespace std;
#include "p326名称空间.cpp"
using namespace Jack; // 如果jack在main()中使用了次编译指令, 那么将视为在函数之外声明的, 但是不会使得太文件中的其他函数能够使用这些名称
int main()
{
// 对于先使用using编译指令后定义局部变量的情况
	double pail = 1;  // 局部变量隐藏了Jack::pail
	cout << pail << endl;
	cin >> Jack::pail;
	cout << Jack::pail << endl; // 但是可以这样解除隐藏

// 对于定于局部变量后加入using编译指令的情况
	int pal = 2;
	cout << pal << endl;
	using namespace Jill;
	cout << pal <<endl;  // 这里使用的还是局部变量, 说明Jill::pal被隐藏了
	cin >> Jill::pal;
	cout << Jill::pal << endl;
	cout << pal << endl;

	return 0;
}

// #############总结using声明和using编译指令的区别###########
// 假设名称空间和声明区域定义了相同的名称, 如果试图使用using声明将名称空间的名称导入该声明区域, 则这两个名称会发生冲突,
// 而且都是后面进行声明的行出错.    如果使用using编译指令将该名称空间的名称导入该声明区域, 则局部版本将隐藏名称空间版本, 
// 而且无论局部变量和编译指令那个先进行写入, 都是编译指令的同名变量被隐藏