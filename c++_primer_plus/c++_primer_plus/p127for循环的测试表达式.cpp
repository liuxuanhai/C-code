// 程序清单 5.2
// for循环中的测试表达式可以为任何表达式, 但是c++会把结果强制转换为bool类型
// 即: 把0转换成false 非零转换成true
#include <iostream>
int main()
{
	using namespace std;

	cout << "输入循环次数:\n";
	int input;
	cin >> input;
	for(int i = input; i; i--) // 把表达式i;转化成了bool类型 bool类型使程序的兼容性更高,
							   // 因为转换成bool类型的时候, 0被转换成了false而非零转换成了true
						       // 而在使用bool类型转换成int的时候 false就是0 true就是1
		// 关于 int i = input; . 变量i将变成属于for的局部自动变量, 不能再for外使用
		//               	   . 这并不是一条表达式, 而只能算作一条语句, 表达式都有值, 
	    //                       而int i只是一个声明语句
		cout << "i = " << i << endl;
	cout << "循环外边的i: " << i << endl;

	return 0;
}